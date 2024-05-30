//
// Created by Alexandra Petrea on 27.05.2024.
//
#include "Mitarbeiter.h"
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <regex>
#include <tuple>

Mitarbeiter::Mitarbeiter(const std::string& lastName, const std::string& firstName, const std::string& email, const std::string& position, const std::string& abbreviation, const std::string& birthDateString, double salary, const std::string& remarks, bool isAdmin)
        : lastName(lastName),
          firstName(firstName),
          email(email),
          position(position),
          abbreviation(abbreviation),
          salary(salary),
          remarks(remarks),
          isActive(false),
          isAdmin(isAdmin) {
    this->birthDate = birthDateString;
    validateEmail(email);
    validateSalary(salary);
    validateAge(birthDate);
}

std::string Mitarbeiter::getLastName() const { return lastName; }
std::string Mitarbeiter::getFirstName() const { return firstName; }
std::string Mitarbeiter::getEmail() const { return email; }
std::string Mitarbeiter::getPosition() const { return position; }
std::string Mitarbeiter::getAbbreviation() const { return abbreviation; }
std::string Mitarbeiter::getRemarks() const { return remarks; }
std::string Mitarbeiter::getBirthDate() const { return birthDate; }
double Mitarbeiter::getSalary() const { return salary; }
bool Mitarbeiter::getIsActive() const { return isActive; }
bool Mitarbeiter::getIsAdmin() const { return isAdmin; }

void Mitarbeiter::setLastName(const std::string &lastName) { this->lastName = lastName; }
void Mitarbeiter::setFirstName(const std::string &firstName) { this->firstName = firstName; }
void Mitarbeiter::setEmail(const std::string &email) { this->email = email; }
void Mitarbeiter::setPosition(const std::string &position) { this->position = position; }
void Mitarbeiter::setAbbreviation(const std::string &abbreviation) { this->abbreviation = abbreviation; }
void Mitarbeiter::setRemarks(const std::string &remarks) { this->remarks = remarks; }
void Mitarbeiter::setBirthDate(const std::string &birthDateString) { this->birthDate = birthDateString; }
void Mitarbeiter::setSalary(double salary) { this->salary = salary; }
void Mitarbeiter::setActive(bool isActive) { this->isActive = isActive; }
void Mitarbeiter::setAdmin(bool isAdmin) { this->isAdmin = isAdmin; }

void Mitarbeiter::validateEmail(const std::string &email) {
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

std::tuple<int, int, int> Mitarbeiter::parseDate(const std::string& date) {
    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));
    return std::make_tuple(day, month, year);
}

int Mitarbeiter::howManyDays(const std::string& date) {
    int day, month, year;
    std::tie(day, month, year) = parseDate(date);
    int days = year * 365 + (year / 4) - (year / 100) + (year / 400); // Leap year adjustment

    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    for (int i = 0; i < month - 1; ++i) {
        days += daysInMonth[i];
    }
    days += day;

    return days;
}

void Mitarbeiter::validateAge(const std::string &birthDate) {
    std::string currentDate = "29.05.2024";
    int age = (howManyDays(currentDate) - howManyDays(birthDate)) / 365;
//	if (age < 0 || age > 80) {
//		throw std::runtime_error("Invalid age");
//	}
}