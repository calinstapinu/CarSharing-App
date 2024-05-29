#include "AdminRepo.h"
#include <iostream>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"

void AdminRepo::read_from_file(const std::string &filename) {
    std::ifstream f(filename);
    if(!f.is_open()) {
        std::cerr<<"Failed to open file for reading"<<'\n';
        return;
    }
    json j;
    f>>j;
    if(j.is_array())
        for (const auto& adminJson:j)
            admins.push_back(adminJson);
    f.close();
}

void AdminRepo::write_to_file(std::string& filename) {
    std::ofstream f(filename);
    if(f.is_open()) {
        f<<this->admins.dump(4);
        f.close();
        return;
    }
    throw std::runtime_error("Error opening "+filename);
}


bool AdminRepo::verify_admin(Admin& admin) const {
    if(admin.getEmail().empty())
        return false;
    return true;
}

void AdminRepo::save() {
    write_to_file(filename);
}

AdminRepo::AdminRepo(const std::string& filename) {
    this->filename=filename;
    read_from_file(this->filename);
}

json & AdminRepo::get_admin_json() {
    return admins;
}

void AdminRepo::add_admin(Admin &admin) {
    if(!verify_admin(admin))
        throw std::runtime_error("Invalid admin details");
    admin.validateEmail(admin.getEmail());
    admin.validateSalary(admin.getSalary());
    json j;
    j["First Name"]=admin.getFirstName();
    j["Last Name"]=admin.getLastName();
    j["Email"]=admin.getEmail();
    j["Position"]=admin.getPosition();
    j["Birthday"]=admin.getBirthday().to_json();
    j["Initials"]=admin.getInitials();
    j["Salary"]=admin.getSalary();
    j["Notes"]=admin.getNotes();
    j["is Active"]=admin.getIsActive();
    j["Password"]=admin.getPassword();
    admins.push_back(j);
    write_to_file(filename);
}

//void AdminRepo::remove_admin(const std::string &identifier) {
//    auto it=std::find_if(admins.begin(),admins.end(),[&](const json& adm){
//        return adm["Email"]==identifier;
//    });
//    if(it!=admins.end()) {
//        admins.erase(it);
//        save();
//    } else
//        throw std::runtime_error("Admin not found");
//}

void AdminRepo::remove_admin(const std::string& identifier) {
    auto it = std::find_if(admins.begin(), admins.end(), [&](const json& adm) {
        return adm["Email"] == identifier;
    });
    if (it != admins.end()) {
        admins.erase(it);
        save();
    } else {
        throw std::runtime_error("Admin not found");
    }
}





bool AdminRepo::search_admin(const std::string email) const {
    for(auto adm: admins)
        if(adm["Email"]==email)
            return true;
    return false;
}

void AdminRepo::modify_admin(std::string identifier, std::string attribute, std::string value) {
    auto it=std::find_if(admins.begin(),admins.end(),[&](const json& adm){
        return adm["Email"]==identifier;
    });
    if(it!=admins.end()) {
        if(attribute=="First Name")
            (*it)["First Name"]=value;
        else if(attribute=="Last Name")
            (*it)["Last Name"]=value;
        else if(attribute=="Email")
            (*it)["Email"]=value;
        else if(attribute=="Position")
            (*it)["Position"]=value;
        else if(attribute=="Birthday")
            (*it)["Birthday"]=value;
        else if(attribute=="Initials")
            (*it)["Initials"]=value;
        else if(attribute=="Salary") {
            int salary=std::stoi(value);
            (*it)["Salary"]=salary;
        }
        else if(attribute=="Notes")
            (*it)["Notes"]=value;
        else if(attribute=="is Active")
            (*it)["is Active"]=(value=="true");
        else if(attribute=="Password")
            (*it)["Password"]=value;
        else
            throw std::runtime_error("Invalid attribute");
        save();
    }
    else
        throw std::runtime_error("Admin not found");
}

