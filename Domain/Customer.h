//
// Created by Home on 5/29/2024.
//

#ifndef JSON_TEST_CUSTOMER_H
#define JSON_TEST_CUSTOMER_H

#include <string>

class Customer {
private:
    std::string id;
    std::string lastName;
    std::string firstName;
    std::string email;
    std::string mobile;
    std::string address;
    std::string remarks;
    std::string password;
    bool gdprDeleted;
public:


    Customer(std::string id, std::string lastName, std::string firstName, std::string email,
             std::string mobile, std::string address, std::string remarks, std::string password, bool gdprDeleted);
    // Getter and Setter for 'id'
    std::string getId() const { return id; }
    void setId(std::string id) { this->id = id; }

    // Getter and Setter for 'lastName'
    const std::string& getLastName() const { return lastName; }
    void setLastName(const std::string& lastName) { this->lastName = lastName; }

    // Getter and Setter for 'firstName'
    const std::string& getFirstName() const { return firstName; }
    void setFirstName(const std::string& firstName) { this->firstName = firstName; }

    // Getter and Setter for 'email'
    const std::string& getEmail() const { return email; }
    void setEmail(const std::string& email) { this->email = email; }

    // Getter and Setter for 'mobile'
    const std::string& getMobile() const { return mobile; }
    void setMobile(const std::string& mobile) { this->mobile = mobile; }

    // Getter and Setter for 'address'
    const std::string& getAddress() const { return address; }
    void setAddress(const std::string& address) { this->address = address; }

    // Getter and Setter for 'remarks'
    const std::string& getRemarks() const { return remarks; }
    void setRemarks(const std::string& remarks) { this->remarks = remarks; }

    // Getter and Setter for 'gdprDeleted'
    bool isGdprDeleted() const { return gdprDeleted; }
    void setGdprDeleted(bool gdprDeleted) { this->gdprDeleted = gdprDeleted; }

    const std::string& getPassword() const {
        return password;
    }

    // Setter for 'password'
    void setPassword(const std::string& newPassword) {
        password = newPassword;
    }

    void anonymize();
};


#endif //JSON_TEST_CUSTOMER_H