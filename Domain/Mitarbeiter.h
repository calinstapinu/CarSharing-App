
#pragma once

#include <string>

using namespace std;

class Mitarbeiter{
private:

    std::string firstName;
    std::string lastName;
    std::string email;
    std::string position;
    std::string abbreviation;
    std::string remarks;
    std::string birthDate;
    double salary;
    bool isActive;
    bool isAdmin;
    std::string password;

public:
    Mitarbeiter(const std::string& lastName, const std::string& firstName, const std::string& email, const std::string& position, const std::string& abbreviation, const std::string& birthDateString, double salary, const std::string& remarks, bool isAdmin);
    std::string getLastName() const;
    std::string getFirstName() const;
    std::string getEmail() const;
    std::string getPosition() const;
    std::string getAbbreviation() const;
    std::string getRemarks() const;
    std::string getBirthDate() const;
    double getSalary() const;
    bool getIsActive() const;
    bool getIsAdmin() const;
    std::string getPassword() const;

    void setLastName(const std::string& lastName);
    void setFirstName(const std::string& firstName);
    void setEmail(const std::string& email);
    void setPosition(const std::string& position);
    void setAbbreviation(const std::string& abbreviation);
    void setRemarks(const std::string& remarks);
    void setBirthDate(const std::string& birthDateString);
    void setSalary(double salary);
    void setActive(bool isActive);
    void setAdmin(bool isAdmin);
    void setPassword(const std::string& password);

    static std::tuple<int, int, int> parseDate(std::string date);
    static int howManyDays(std::string date);


    static void validateEmail(const std::string& email);
    static void validateSalary(double salary);
    static void validateAge(const std::string& birthDate);


    void display() const;

};
