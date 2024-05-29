//
// Created by Victor Rusu on 5/28/2024.
//

#include "CustomerRepo.h"
#include <stdexcept>
#include <exception>
#include <regex>
#include <algorithm>


json &CustomerRepo::getCustomers() {
    return customers;
}

void CustomerRepo::read_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return;
    }

    json j;
    file >> j;

    if (j.is_array())
        for (const auto& clientJson : j)
            customers.push_back(clientJson);
    file.close();
}

void CustomerRepo::write_to_file(std::string& filename) {
    std::ofstream file(filename);
    if(file.is_open()) {
        file << this->customers.dump(4); // array-ul intreg este scris in fisier
        file.close();                      // cu indent 4
        return;
    }
    throw std::runtime_error("Error opening " + filename);

}

void CustomerRepo::createCustomer(const Customer &customer) {
    if(validateCustomer(customer)){
        json j;
        j["password"] = customer.getPassword();
        j["lastName"] = customer.getLastName();
        j["firstName"] = customer.getFirstName();
        j["mobile"] = customer.getMobile();
        j["remarks"] = customer.getRemarks();
        j["email"] = customer.getEmail();
        j["address"] = customer.getAddress();
        j["id"] = customer.getId();
        j["gdprDeleted"] = customer.isGdprDeleted();
        customers.push_back(j);
        write_to_file(filename);
    } else throw std::exception();

}

CustomerRepo::CustomerRepo(const std::string &filename): filename(filename) {
    read_from_file(filename);

}

bool CustomerRepo::validateCustomer(const Customer &customer) {
    // Check if essential fields are empty
    if (!customer.isGdprDeleted()) {
        if (customer.getEmail().empty() || customer.getMobile().empty() || customer.getAddress().empty() ||
            customer.getFirstName().empty() || customer.getLastName().empty())
            return false;
    } else {
        if (customer.getLastName().empty() || customer.getFirstName().empty())
            return false;
    }

    // Validate email format
    static const std::regex email_pattern(
            R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)"
    );
    if (!std::regex_match(customer.getEmail(), email_pattern))
        return false;

    // Validate mobile number format
    static const std::regex mobile_pattern(
            R"(^\+?[0-9]+$)"
    );
    if (!std::regex_match(customer.getMobile(), mobile_pattern))
        return false;

    // Check for duplicate email (if applicable)
    // Note: Update this part based on the actual structure of the 'customers' container

    return true; // Customer is valid
}


void CustomerRepo::removeCustomer(const std::string& identifier) {
    auto it = std::find_if(customers.begin(),customers.end(),[&](const json& emp) {
        return emp["email"] == identifier;
    });

    if(it != customers.end()){
        customers.erase(it);
        write_to_file(filename);
    }

}

void
CustomerRepo::modifyCustomer(const std::string &identifier, const std::string &attribute, const std::string &value) {
    auto it = std::find_if(customers.begin(),customers.end(),[&](const json& emp) {
        return emp["email"] == identifier;
    });

    if(it!=customers.end()){
        (*it)[attribute] = value;
    }
}

Customer CustomerRepo::searchAfterEmail(const std::string& email) {
    for(auto& it:customers){
        if(it["email"] == email)
            return {it["id"],it["lastName"],it["firstName"],it["email"],it["mobile"],it["address"],it["remarks"],it["password"],it["gdprDeleted"]};
    }

    return {"0","","","","","","","",false};
}

Customer CustomerRepo::searchAfterMobile(const std::string& mobile) {
    for(auto& it:customers){
        if(it["mobile"] == mobile)
            return {it["id"],it["lastName"],it["firstName"],it["email"],it["mobile"],it["address"],it["remarks"],it["password"],it["gdprDeleted"]};
    }

    return {"0","","","","","","","",false};
}

std::vector<Customer> CustomerRepo::searchAfterName(const std::string& name) {
    std::vector<Customer> result;

    for(auto& it:customers){
        if(it["firstName"] == name || it["lastName"] == name)
            result.emplace_back(it["id"],it["lastName"],it["firstName"],it["email"],it["mobile"],it["address"],it["remarks"],it["password"],it["gdprDeleted"]);
    }

    return result;


}