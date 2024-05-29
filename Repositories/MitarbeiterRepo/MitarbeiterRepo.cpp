#include "MitarbeiterRepo.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <typeinfo>
#include <iostream>


MitarbeiterRepo::MitarbeiterRepo(const std::string& filename) {
    this->filename = filename;
    this->read_from_file(this->filename);
}

void MitarbeiterRepo::write_to_file(const string &filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << this->mitarbeiter.dump(4); // Pretty print with an indent of 4 spaces
        file.close();
        return;
    }
    throw runtime_error("Unable to open file: " + filename);

}


void MitarbeiterRepo::read_from_file(const string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return;
    }

    json j;
    file >> j; // se citeste tot array-ul din fisier

    if (j.is_array())
        for (const auto& carJson : j)
            this->mitarbeiter.push_back(carJson); // fiecare obiect json din array este
    file.close();                              // introdus in array
}


bool MitarbeiterRepo::verify_employee(Mitarbeiter employee) const {
    for (const auto& emp : mitarbeiter) {
        if (emp["email"] == employee.getEmail()) {
            return false;
        }
        //employee.validateAge(employee.getBirthDate());
    }
    return true;
}

void MitarbeiterRepo::save() {
    write_to_file(filename);

}

json& MitarbeiterRepo::get_mitarbeiter_json() {
    return mitarbeiter;
}

void MitarbeiterRepo::remove_employee(const std::string& identifier) {
    auto it = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == identifier;
    });

    if (it != mitarbeiter.end()) {
        if ((*it)["isActive"]) {
            throw std::runtime_error("Cannot remove an active employee.");
        }
        mitarbeiter.erase(it);
        save();
    } else {
        throw std::runtime_error("Employee not found.");
    }
}


void MitarbeiterRepo::add_employee(const Mitarbeiter& employee) {
    //if (!this->verify_employee(employee))throw std::runtime_error("Invalid age");
    json j;
    j["lastName"] = employee.getLastName();
    j["firstName"] = employee.getFirstName();
    j["email"] = employee.getEmail();
    j["position"] = employee.getPosition();
    j["abbreviation"] = employee.getAbbreviation();
    j["remarks"] = employee.getRemarks();
    j["birthDate"] = employee.getBirthDate();
    j["salary"] = employee.getSalary();
    j["isActive"] = employee.getIsActive();
    j["isAdmin"] = employee.getIsAdmin();
    this->mitarbeiter.push_back(j);
    this->write_to_file(this->filename);
}

void MitarbeiterRepo::modify_employee(const std::string& identifier, const std::string& attribute, const std::string& value) {
    auto it = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == identifier;
    });

    if (it != mitarbeiter.end()) {
        if (attribute == "lastName") {
            (*it)["lastName"] = value;
        } else if (attribute == "firstName") {
            (*it)["firstName"] = value;
        } else if (attribute == "email") {
            Mitarbeiter::validateEmail(value);
            (*it)["email"] = value;
        } else if (attribute == "position") {
            (*it)["position"] = value;
        } else if (attribute == "abbreviation") {
            (*it)["abbreviation"] = value;
        } else if (attribute == "remarks") {
            (*it)["remarks"] = value;
        } else if (attribute == "birthDate") {
            (*it)["birthDate"] = value; // This should be converted to the correct format
        } else if (attribute == "salary") {
            double salary = std::stod(value);
            Mitarbeiter::validateSalary(salary);
            (*it)["salary"] = salary;
        } else if (attribute == "isActive") {
            (*it)["isActive"] = (value == "true");
        } else if (attribute == "isAdmin") {
            (*it)["isAdmin"] = (value == "true");
        } else {
            throw std::runtime_error("Invalid attribute.");
        }
        save();
    } else {
        throw std::runtime_error("Employee not found.");
    }
}
///asta nu stiu daca vine in repo
bool MitarbeiterRepo::search_employee(const std::string& identifier) const {
    auto it = std::find_if(mitarbeiter.begin(), mitarbeiter.end(), [&](const json& emp) {
        return emp["abbreviation"] == identifier;
    });
    return it != mitarbeiter.end();
}
