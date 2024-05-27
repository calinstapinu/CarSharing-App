//
// Created by Alexandra Petrea on 27.05.2024.
//
#include "Mitarbeiter.h"
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <regex>


Mitarbeiter::Mitarbeiter(const std::string& lastName, const std::string& firstName, const std::string& email, const std::string& position, const std::string& abbreviation, const std::string& birthDateString, double salary, const std::string& remarks, bool isAdmin)
        : lastName(lastName),
          firstName(firstName),
          email(email),
          position(position),
          abbreviation(abbreviation),
          remarks(remarks),
          salary(salary),
          isActive(true),
          isAdmin(isAdmin) {
    this->birthDate = parseDate(birthDateString);
    validateEmail(email);
    validateSalary(salary);
    validateAge(birthDate);
}

std::string Mitarbeiter::getLastName() const {
    return lastName;
}

std::string Mitarbeiter::getFirstName() const {
    return firstName;
}

std::string Mitarbeiter::getEmail() const {
    return email;
}

std::string Mitarbeiter::getPosition() const {
    return position;
}

std::string Mitarbeiter::getAbbreviation() const {
    return abbreviation;
}

std::string Mitarbeiter::getRemarks() const {
    return remarks;
}

std::tm Mitarbeiter::getBirthDate() const {
    return birthDate;
}

double Mitarbeiter::getSalary() const {
    return salary;
}

bool Mitarbeiter::getIsActive() const {
    return isActive;
}

bool Mitarbeiter::getIsAdmin() const {
    return isAdmin;
}

void Mitarbeiter::setLastName(const string &lastName) {
    this->lastName = lastName;
}

void Mitarbeiter::setFirstName(const string &firstName) {
    this->firstName = firstName;
}

void Mitarbeiter::setEmail(const string &email) {
    this->email = email;
}

void Mitarbeiter::setPosition(const string &position) {
    this->position = position;
}

void Mitarbeiter::setAbbreviation(const string &abbreviation) {
    this->abbreviation = abbreviation;
}

void Mitarbeiter::setRemarks(const string &remarks) {
    this->remarks = remarks;
}

void Mitarbeiter::setBirthDate(const string &birthDateString) {
    this->birthDate = birthDate;
}

void Mitarbeiter::setSalary(double salary) {
    this->salary = salary;
}

void Mitarbeiter::setActive(bool isActive) {
    this->isActive = isActive;
}

void Mitarbeiter::setAdmin(bool isAdmin) {
    this->isAdmin = isAdmin;
}

std::tm Mitarbeiter::parseDate(const string &dateStr) {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%d.%m.%Y");
    if (ss.fail()) {
        throw std::runtime_error("Invalid date format. Expected format: dd.mm.yyyy");
    }
    return tm;

}

void Mitarbeiter::validateEmail(const string &email) {
    const std::regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.{1}\w+)+)");
    if (!std::regex_match(email, pattern)) {
        throw std::runtime_error("Invalid email format: " + email);
    }
}

void Mitarbeiter::validateSalary(double salary) {
    if (salary < 100) {
        throw std::runtime_error("Salary must be at least 100 EUR. Provided salary: " + std::to_string(salary));
    }
}

void Mitarbeiter::validateAge(const tm &birthDate) {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    int age = now->tm_year + 1900 - birthDate.tm_year;
    if ((now->tm_mon < birthDate.tm_mon) || (now->tm_mon == birthDate.tm_mon && now->tm_mday < birthDate.tm_mday)) {
        age--;
    }
    if (age < 0 || age > 80) {
        throw std::runtime_error("Age must be between 0 and 80 years. Calculated age: " + std::to_string(age));
    }
}







