//
// Created by Home on 5/30/2024.
//
#include "CustomerController.h"
#include <algorithm>
#include <iostream>

CustomerController::CustomerController(const std::string& filename) : customerRepo(filename) {}

void CustomerController::addCustomer(const Customer& customer) {
    customerRepo.createCustomer(customer);
}

bool CustomerController::deleteCustomer(const std::string& email) {
    // Example check, actual logic to verify if the customer has orders should be implemented
    auto customer = customerRepo.searchAfterEmail(email);
    if (!customer.isGdprDeleted() && customer.getId() != "0") { // Check if customer exists and has no orders
        customerRepo.removeCustomer(email);
        return true;
    }
    return false;
}

void CustomerController::updateCustomer(const std::string& email, const std::string& attribute, const std::string& value) {
    customerRepo.modifyCustomer(email, attribute, value);
}

void CustomerController::anonymizeCustomer(const std::string& email) {
    auto customer = customerRepo.searchAfterEmail(email);
    if (!customer.getId().empty()) {
        // Modify and anonymize the customer details according to GDPR rules
        customerRepo.modifyCustomer(email, "lastName", "Kunde-" + customer.getId());
        customerRepo.modifyCustomer(email, "firstName", "Unbekannt");
        customerRepo.modifyCustomer(email, "email", "");
        customerRepo.modifyCustomer(email, "mobile", "");
        customerRepo.modifyCustomer(email, "address", "");
        customerRepo.modifyCustomer(email, "remarks", "");
        customerRepo.modifyCustomer(email, "gdprDeleted", "true");
    }
}

std::vector<Customer> CustomerController::getAllCustomersSortedByName() {
    auto customers = customerRepo.getCustomers();
    std::vector<Customer> sortedCustomers;
    for (auto& cust : customers) {
        Customer customer(cust["id"], cust["lastName"], cust["firstName"], cust["email"], cust["mobile"], cust["address"], cust["remarks"], cust["password"], cust["gdprDeleted"]);
        sortedCustomers.emplace_back(customer);
    }

    std::sort(sortedCustomers.begin(), sortedCustomers.end(), [](const Customer& a, const Customer& b) {
        return a.getLastName() < b.getLastName() || (a.getLastName() == b.getLastName() && a.getFirstName() < b.getFirstName());
    });

    return sortedCustomers;
}

Customer CustomerController::findCustomerByEmail(const std::string& email) {
    return customerRepo.searchAfterEmail(email);
}

Customer CustomerController::findCustomerByMobile(const std::string& mobile) {
    return customerRepo.searchAfterMobile(mobile);
}

std::vector<Customer> CustomerController::findCustomersByName(const std::string& name) {
    return customerRepo.searchAfterName(name);
}