#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H

#include <string>
#include <vector>
#include "../Repositories/AdminRepo/AdminRepo.h"
#include "../Domain/Admin.h"

class AdminController {
public:
    AdminController(AdminRepo& adminRepo);

    void createAdmin(const std::string& lastName, const std::string& firstName, const std::string& email, const std::string& position, const std::string& abbreviation, const Date& birthDate, double salary, const std::string& remarks, bool isActive, const std::string& password);
    void updateAdmin(const std::string& identifier, const std::string& attribute, const std::string& value);
    void deleteAdmin(const std::string& identifier);
    void activateAdmin(const std::string& identifier);
    void deactivateAdmin(const std::string& identifier);
    void resetAdminPassword(const std::string& identifier);

    void listAllAdmins() const;
    std::vector<Admin> searchAdminsByName(const std::string& name) const;
    void viewAdminSalary(const std::string& identifier) const;
    void adjustAdminSalary(const std::string& identifier, double newSalary);

private:
    AdminRepo& adminRepo;
    std::string generateRandomPassword() const;
    void sendPasswordResetEmail(const std::string& email, const std::string& newPassword) const;
    static Admin jsonToAdmin(const nlohmann::json& adminJson);
};

#endif // ADMINCONTROLLER_H
