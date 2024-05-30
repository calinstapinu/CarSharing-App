//
// Created by Tudor on 29.05.2024.
//
#include "MitarbeiterController.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
using namespace std;

MitarbeiterController::MitarbeiterController(const std::string& filename) : repo(filename) {}

void MitarbeiterController::add_employee(const string& lastName, const string& firstName, const string& email, const string& position, const string& abbreviation, const string& birthDateString, double salary, const string& remarks, bool isAdmin) {
    Mitarbeiter employee(lastName, firstName, email, position, abbreviation, birthDateString, salary, remarks, isAdmin);
    repo.add_employee(employee);
}

void MitarbeiterController::modify_employee(const string& identifier, const string& attribute, const string& value) {
    repo.modify_employee(identifier, attribute, value);
}

void MitarbeiterController::remove_employee(const string& identifier) {
    repo.remove_employee(identifier);
}

//void MitarbeiterController::stergere(const string& abbreviation){
//	repo.remove_employee(abbreviation);
//}


void MitarbeiterController::list_all_employees() const {
    const json& employees = repo.get_mitarbeiter_json();
    for (const auto& emp : employees) {
        std::cout << emp.dump(4) << std::endl;
    }
}

bool MitarbeiterController::search_employee(const string& identifier) const {
    return repo.search_employee(identifier);
}

void MitarbeiterController::activateEmployee(const std::string& identifier) {
    repo.modify_employee(identifier, "isActive", "true");
}

void MitarbeiterController::deactivateEmployee(const std::string& identifier) {
    repo.modify_employee(identifier, "isActive", "false");
}

void MitarbeiterController::assignAdminRights(const std::string& identifier) {
    repo.modify_employee(identifier, "isAdmin", "true");
}

void MitarbeiterController::removeAdminRights(const std::string& identifier) {
    repo.modify_employee(identifier, "isAdmin", "false");
}

void MitarbeiterController::changeOwnRemarks(const std::string& identifier, const std::string& remarks) {
    repo.modify_employee(identifier, "remarks", remarks);
}

Mitarbeiter MitarbeiterController::searchEmployeeByEmail(const string& email) const {
    json employeesJson = repo.get_mitarbeiter_json();
    for (const auto& empJson : employeesJson) {
        if (empJson["email"] == email) {
            return jsonToMitarbeiter(empJson);
        }
    }
    throw runtime_error("Employee not found.");
}

vector<Mitarbeiter> MitarbeiterController::searchEmployeeByName(const std::string& lastName, const std::string& firstName) const {
    vector<Mitarbeiter> employees;
    json employeesJson = repo.get_mitarbeiter_json();
    for (const auto& empJson : employeesJson) {
        if (empJson["lastName"] == lastName && empJson["firstName"] == firstName) {
            employees.push_back(jsonToMitarbeiter(empJson));
        }
    }
    return employees;
}

vector<Mitarbeiter> MitarbeiterController::searchEmployeeByBirthDate(const std::string& startDate, const std::string& endDate) const {
    vector<Mitarbeiter> employees;
    json employeesJson = repo.get_mitarbeiter_json();
    for (const auto& empJson : employeesJson) {
        string birthDate = empJson["birthDate"];
        if (birthDate >= startDate && birthDate <= endDate) {
            employees.push_back(jsonToMitarbeiter(empJson));
        }
    }
    return employees;
}

void MitarbeiterController::validateAdminAccess(const std::string& identifier) const {
    json employeesJson = repo.get_mitarbeiter_json();
    for (const auto& empJson : employeesJson) {
        if (empJson["abbreviation"] == identifier && empJson["isAdmin"]) {
            return;
        }
    }
    throw runtime_error("Access denied. Admin rights required.");
}

Mitarbeiter MitarbeiterController::jsonToMitarbeiter(const nlohmann::json& empJson) const{
    if (!empJson.contains("lastName") || !empJson.contains("firstName")
        || !empJson.contains("email") || !empJson.contains("position")
        || !empJson.contains("birthDate") || !empJson.contains("abbreviation")
        || !empJson.contains("salary") || !empJson.contains("remarks")
        || !empJson.contains("isActive") || !empJson.contains("isAdmin")) {
        throw runtime_error("Incomplete Mitarbeiter data in JSON");
    }

    string lastName = empJson["lastName"];
    string firstName = empJson["firstName"];
    string email = empJson["email"];
    string position = empJson["position"];
    string abbreviation = empJson["abbreviation"];
    string birthDateString = empJson["birthDate"];
    if (!empJson["salary"].is_number()) {
        throw runtime_error("Invalid salary in JSON");
    }
    double salary = empJson["salary"];
    string remarks = empJson.value("remarks", "");
    bool isAdmin = empJson["isAdmin"];
    return Mitarbeiter(lastName, firstName, email, position, abbreviation,
                       birthDateString, salary, remarks, isAdmin);
}