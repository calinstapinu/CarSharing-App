//
// Created by Tudor on 29.05.2024.
//
#ifndef JSON_TEST_MITARBEITERCONTROLLER_H
#define JSON_TEST_MITARBEITERCONTROLLER_H
#include <vector>
#include <string>
#include "../Domain/Mitarbeiter.h"
#include "../Repositories/MitarbeiterRepo/MitarbeiterRepo.h"

class MitarbeiterController {
public:
    explicit MitarbeiterController(const std::string& filename);

    void add_employee(const std::string& lastName, const std::string& firstName, const std::string& email, const std::string& position, const std::string& abbreviation, const std::string& birthDateString, double salary, const std::string& remarks, bool isAdmin);
    void modify_employee(const std::string& identifier, const std::string& attribute, const std::string& value);
    void remove_employee(const std::string& identifier);
    bool search_employee(const std::string& identifier) const;
    void list_all_employees() const;
    void activateEmployee(const std::string &identifier);
    void deactivateEmployee(const std::string &identifier);
    void assignAdminRights(const std::string &identifier);
    void removeAdminRights(const std::string &identifier);
    void changeOwnRemarks(const std::string &identifier, const std::string &remarks);
    Mitarbeiter searchEmployeeByEmail(const std::string &email) const;
    std::vector<Mitarbeiter> searchEmployeeByName(const std::string &lastName, const std::string &firstName) const;
    std::vector<Mitarbeiter> searchEmployeeByBirthDate(const std::string &startDate, const std::string &endDate) const;
    void validateAdminAccess(const std::string &identifier) const;
    //void stergere(const std::string &abbreviation);
    Mitarbeiter jsonToMitarbeiter(const nlohmann::json& empJson) const;

private:
    MitarbeiterRepo repo;

};

#endif //JSON_TEST_MITARBEITERCONTROLLER_H