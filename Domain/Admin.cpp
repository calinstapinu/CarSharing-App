#include "Admin.h"
#include <regex>

Admin::Admin(std::string firstName, std::string lastName, std::string email, std::string position, Date birthday,
             std::string initials, int salary, std::string notes, std::string password)
        :firstName(firstName),lastName(lastName),email(email),position(position),birthday(birthday),initials(initials),salary(salary),notes(notes), password(password)
{
}

Admin::Admin(std::string firstName, std::string lastName, std::string email, std::string position, Date birthday,
             std::string initials, int salary, std::string password)
        :firstName(firstName),lastName(lastName),email(email),position(position),birthday(birthday),initials(initials),salary(salary),notes(""),password(password)
{
}

std::string Admin::getFirstName() {
    return firstName;
}

std::string Admin::getLastName() {
    return lastName;
}

std::string Admin::getEmail() {
    return email;
}

std::string Admin::getPosition() {
    return position;
}

Date Admin::getBirthday() {
    return birthday;
}

std::string Admin::getInitials() {
    return initials;
}

int Admin::getSalary() {
    return salary;
}

std::string Admin::getNotes() {
    return notes;
}

bool Admin::getIsActive() {
    return isActive;
}

std::string Admin::getPassword() {
    return password;
}

void Admin::setFirstName(std::string newFirstName) {
    firstName=newFirstName;
}

void Admin::setLastName(std::string newLastName) {
    lastName=newLastName;
}

void Admin::setEmail(std::string newEmail) {
    email=newEmail;
}

void Admin::setPosition(std::string newPosition) {
    position=newPosition;
}

void Admin::setBirthday(Date newBirthday) {
    birthday=newBirthday;
}

void Admin::setInitials(std::string newInitials) {
    initials=newInitials;
}

void Admin::setSalary(int newSalary) {
    salary=newSalary;
}

void Admin::setNotes(std::string newNotes) {
    notes=newNotes;
}

void Admin::setIsActive(bool newIsActive) {
    isActive=newIsActive;
}

void Admin::setPassword(std::string newPassword) {
    password=newPassword;
}

void Admin::validateEmail(const std::string &email) {
    const std::regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.{1}\w+)+)");
    if (!std::regex_match(email, pattern)) {
        throw std::runtime_error("Invalid email format: " + email);
    }
}

void Admin::validateSalary(double salary) {
    if (salary < 100) {
        throw std::runtime_error("Salary must be at least 100 EUR. Provided salary: " + std::to_string(salary));
    }
}

void Admin::validateBirthday(Date birthday) {
    if(birthday.year<=1944 || birthday.year>2024)
        throw std::runtime_error("Admin must be between 0 and 80 years old");
}