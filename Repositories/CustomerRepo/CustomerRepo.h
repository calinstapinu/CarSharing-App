//
// Created by Victor Rusu on 5/28/2024.
//

#ifndef JSON_TEST_CustomerREPO_H
#define JSON_TEST_CustomerREPO_H

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "../include/nlohmann/json.hpp"
#include "nlohmann/json.hpp"
#include "../Domain/Customer.h"

using json = nlohmann::json;

class CustomerRepo {
private:
    json customers;
    std::string filename;

    bool validateCustomer(const Customer& customer);

    void read_from_file(const std::string& filename);

    void write_to_file(std::string& filename);



public:
    CustomerRepo(const std::string& filename);
    void createCustomer(const Customer& customer);
    void removeCustomer(const std::string& identifier);
    void modifyCustomer(const std::string& identifier, const std::string& attribute, const std::string& value);
    Customer searchAfterEmail(const std::string& email);
    Customer searchAfterMobile(const std::string& mobile);
    std::vector<Customer> searchAfterName(const std::string& name);
    json& getCustomers();

};


#endif //JSON_TEST_CustomerREPO_H