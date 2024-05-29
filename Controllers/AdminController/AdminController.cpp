#include "AdminController.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <stdexcept>

AdminController::AdminController(AdminRepo& adminRepo) : adminRepo(adminRepo) {}

std::string AdminController::generateRandomPassword() const {
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string password;
    for (int i = 0; i < 12; ++i) {
        password += characters[distribution(generator)];
    }
    return password;
}

void AdminController::sendPasswordResetEmail(const std::string& email, const std::string& newPassword) const {
    //std::cout << "Sending password reset email to " << email << ":\n";
    //std::cout << "New password: " << newPassword << std::endl;
}

// Admin management functions
void AdminController::createAdmin(const std::string& lastName, const std::string& firstName, const std::string& email, const std::string& position, const std::string& abbreviation, const Date& birthDate, double salary, const std::string& remarks, bool isActive, const std::string& password) {
    try {
        Admin newAdmin(lastName, firstName, email, position, birthDate, abbreviation,
                    salary, remarks, password);
        adminRepo.add_admin(newAdmin);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error creating admin: " << e.what() << std::endl;
    }
}

//void AdminController::updateAdmin(const std::string& identifier, const std::string& attribute, const std::string& value) {
//    try {
//        adminRepo.modify_admin(identifier, attribute, value);
//    } catch (const std::runtime_error& e) {
//        std::cerr << "Error updating admin: " << e.what() << std::endl;
//    }
//}

void AdminController::updateAdmin(const std::string& identifier, const std::string& attribute, const std::string& value) {
    try {
        adminRepo.modify_admin(identifier, attribute, value);
        //std::cout << "Admin updated successfully!" << std::endl;
    } catch (const std::runtime_error& e) {
        //std::cerr << "Error updating admin: " << e.what() << std::endl;
    }
}

void AdminController::deleteAdmin(const std::string& identifier) {
    try {
        adminRepo.remove_admin(identifier);
        //std::cout << "Admin deleted successfully!" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error deleting admin: " << e.what() << std::endl;
    }
}


void AdminController::activateAdmin(const std::string& identifier) {
    updateAdmin(identifier, "is Active", "true");
}

void AdminController::deactivateAdmin(const std::string& identifier) {
    updateAdmin(identifier, "is Active", "false");
}

void AdminController::resetAdminPassword(const std::string& identifier) {
    try {
        json admins = adminRepo.get_admin_json();
        auto it = std::find_if(admins.begin(), admins.end(), [&](const json& adm) {
            return adm["Email"] == identifier;
        });

        if (it != admins.end()) {
            std::string newPassword = generateRandomPassword();
            adminRepo.modify_admin(identifier, "Password", newPassword);
            sendPasswordResetEmail(identifier, newPassword);
            //std::cout << "Password reset successfully and emailed!" << std::endl;
        } else {
            throw std::runtime_error("Admin not found");
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error resetting password: " << e.what() << std::endl;
    }
}

void AdminController::listAllAdmins() const {
    json admins = adminRepo.get_admin_json();
    if (admins.empty()) {
        std::cout << "No admins found in the database." << std::endl;
        return;
    }

    for (const auto& adminJson : admins) {
        Admin admin = jsonToAdmin(adminJson);
        std::cout << admin.getEmail() << std::endl;
    }
}

std::vector<Admin> AdminController::searchAdminsByName(const std::string& name) const {
    std::vector<Admin> admins;
    for (const auto& adminJson : adminRepo.get_admin_json()) {
        Admin admin = jsonToAdmin(adminJson);
        if (admin.getLastName() == name || admin.getFirstName() == name) {
            admins.push_back(admin);
        }
    }
    return admins;
}

void AdminController::viewAdminSalary(const std::string& identifier) const {
    try {
        json admins = adminRepo.get_admin_json();
        auto it = std::find_if(admins.begin(), admins.end(), [&](const json& adm) {
            return adm["Email"] == identifier;
        });

        if (it != admins.end()) {
            Admin admin = jsonToAdmin(*it);
            //std::cout << "The admin's salary is: " << std::fixed << std::setprecision(2) << admin.getSalary() << " EUR" << std::endl;
        } else {
            throw std::runtime_error("Admin not found");
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error viewing salary: " << e.what() << std::endl;
    }
}

void AdminController::adjustAdminSalary(const std::string& identifier, double newSalary) {
    try {
        if (newSalary < 100) {
            throw std::runtime_error("Salary must be at least 100 EUR.");
        }
        adminRepo.modify_admin(identifier, "Salary", std::to_string(newSalary));
        //std::cout << "Admin salary successfully updated!" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error updating salary: " << e.what() << std::endl;
    }
}

Admin AdminController::jsonToAdmin(const nlohmann::json& adminJson) {
    if (!adminJson.contains("Last Name") || !adminJson.contains("First Name")
        || !adminJson.contains("Email") || !adminJson.contains("Position")
        || !adminJson.contains("Birthday") || !adminJson.contains("Initials")
        || !adminJson.contains("Salary") || !adminJson.contains("Password")) {
        throw std::runtime_error("Incomplete Admin data in JSON");
    }

    std::string lastName = adminJson["Last Name"];
    std::string firstName = adminJson["First Name"];
    std::string email = adminJson["Email"];
    std::string position = adminJson["Position"];
    std::string initials = adminJson["Initials"];
    Date birthday = {adminJson["Birthday"]["day"], adminJson["Birthday"]["year"], adminJson["Birthday"]["month"]};

    if (!adminJson["Salary"].is_number()) {
        throw std::runtime_error("Invalid salary in JSON");
    }
    double salary = adminJson["Salary"];
    std::string remarks = adminJson.value("Remarks", "");
    std::string password = adminJson["Password"];

    return Admin(lastName, firstName, email, position, birthday, initials,
                 salary, remarks, password);
}
