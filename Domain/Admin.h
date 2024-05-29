#ifndef ADMIN_H
#define ADMIN_H
#pragma once

#include <string>
#include "../include/nlohmann/json.hpp"

struct Date {
    int day,year;
    std::string month;
    nlohmann::json to_json() const {
        return nlohmann::json{{"day", day}, {"month", month}, {"year", year}};
    }
};

class Admin {
private:
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string position;
    Date birthday;
    std::string initials;
    int salary;
    std::string notes;
    bool isActive;
    std::string password;

public:
    Admin(std::string firstName, std::string lastName, std::string email, std::string position, Date birthday, std::string initials, int salary, std::string notes, std::string password);
    Admin(std::string firstName, std::string lastName, std::string email, std::string position, Date birthday, std::string initials, int salary, std::string password);
    std::string getFirstName();
    std::string getLastName();
    std::string getEmail();
    std::string getPosition();
    Date getBirthday();
    std::string getInitials();
    int getSalary();
    std::string getNotes();
    bool getIsActive();
    std::string getPassword();
    void setFirstName(std::string newFirstName);
    void setLastName(std::string newLastName);
    void setEmail(std::string newEmail);
    void setPosition(std::string newPosition);
    void setBirthday(Date newBirthday);
    void setInitials(std::string newInitials);
    void setSalary(int newSalary);
    void setNotes(std::string newNotes);
    void setIsActive(bool newIsActive);
    void setPassword(std::string newPassword);
    void validateEmail(const std::string &email);
    void validateSalary(double salary);
    void validateBirthday(Date birthday);
};



#endif //ADMIN_H