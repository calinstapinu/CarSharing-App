#ifndef MITARBEITER_H
#define MITARBEITER_H

#include <string>
#include <tuple>

class Mitarbeiter {
public:
    Mitarbeiter(const std::string& lastName, const std::string& firstName, const std::string& email, const std::string& position, const std::string& abbreviation, const std::string& birthDateString, double salary, const std::string& remarks, bool isAdmin);

    // Getters
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

    // Setters
    void setLastName(const std::string &lastName);
    void setFirstName(const std::string &firstName);
    void setEmail(const std::string &email);
    void setPosition(const std::string &position);
    void setAbbreviation(const std::string &abbreviation);
    void setRemarks(const std::string &remarks);
    void setBirthDate(const std::string &birthDateString);
    void setSalary(double salary);
    void setActive(bool isActive);
    void setAdmin(bool isAdmin);

    static void validateEmail(const std::string &email);
    static void validateSalary(double salary);
    static void validateAge(const std::string &birthDate);

private:
    std::string lastName;
    std::string firstName;
    std::string email;
    std::string position;
    std::string abbreviation;
    std::string birthDate;
    double salary;
    std::string remarks;
    bool isActive;
    bool isAdmin;

    static std::tuple<int, int, int> parseDate(const std::string& date);
    static int howManyDays(const std::string& date);
};

#endif // MITARBEITER_H