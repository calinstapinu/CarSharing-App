//
// Created by ANDREI on 29/05/2024.
//

#include "CustomerUI.h"
#include <iostream>
#include <vector>

void CustomerUI::printMenu() {
    std::cout << "Customer Management System" << std::endl;
    std::cout << "1. Add Customer" << std::endl;
    std::cout << "2. Delete Customer" << std::endl;
    std::cout << "3. Update Customer" << std::endl;
    std::cout << "4. Anonymize Customer" << std::endl;
    std::cout << "5. List Customers" << std::endl;
    std::cout << "6. Find Customer" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

void CustomerUI::addCustomer() {
    std::string firstName, lastName, email, address, remarks, phone, password;
//    bool gdprDeleted;

    std::cout << "Enter first name: ";
    std::cin >> firstName;
    std::cout << "Enter last name: ";
    std::cin >> lastName;
    std::cout << "Enter email: ";
    std::cin >> email;
    std::cout << "Enter password";
    std::cin >> password;
    std::cout << "Enter address: ";
    std::cin >> address;
    std::cout << "Enter remarks: ";
    std::cin >> remarks;
    std::cout << "Enter phone: ";
    std::cin >> phone;
//    std::cout << "Is GDPR deleted (1 for Yes, 0 for No): ";
//    std::cin >> gdprDeleted;

    try {

        customerController.addCustomer(firstName, lastName, email, password, address, remarks, phone);
        std::cout << "Customer added successfully!" << std::endl;
    }
    catch (std::invalid_argument e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void CustomerUI::deleteCustomer() {
    std::string email;

    std::cout << "Enter Email of the customer to delete: ";
    std::cin >> email;

    customerController.deleteCustomer(email);
    std::cout << "Customer deleted successfully!" << std::endl;
}

void CustomerUI::updateCustomer() {
    std::string name, surname, email, address, remarks, phone,password,favoriteCars;
    bool gdprDeleted;

    std::cout << "Enter Email of the customer to update: ";
    std::cin >> email;
    std::cout << "Enter new Name: ";
    std::cin >> password;
    std::cout << "Enter new Password";
    std::cin >> name;
    std::cout << "Enter new Surname: ";
    std::cin >> surname;
    std::cout << "Enter new Address: ";
    std::cin >> address;
    std::cout << "Enter new Remarks: ";
    std::cin >> remarks;
    std::cout << "Enter new Phone: ";
    std::cin >> phone;
    std::cout << "Is GDPR Deleted (1 for Yes, 0 for No): ";
    std::cin >> gdprDeleted;

    CustomerUI updatedCustomer(name, surname, email, phone, address, remarks, password, gdprDeleted)
    try {
        customerController.updateCustomer(updatedCustomer);
        std::cout << "Customer updated successfully!" << std::endl;
    }
    catch (std::invalid_argument e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void CustomerUI::getAllCustomersSortedByName() {
    std::vector<Customer> customers = customerController.getAllCustomersSortedByName();
    for (auto customer : customers) {
        std::cout << customer.toString() << std::endl;
    }
}

void CustomerUI::findCustomerByEmail() {
    std::string email;

    std::cout << "Enter Email to search: ";
    std::cin >> email;

    std::vector<Customer> results = customerController.findCustomerByEmail(email);
    if (results.empty()) {
        std::cout << "No customers found with the given email." << std::endl;
    } else {
        for (auto customer : results) {
            std::cout << customer.toString() << std::endl;
        }
    }
}

void CustomerUI::findCustomerByMobile() {
    std::string phoneNumber;

    std::cout << "Enter Phone Number to search: ";
    std::cin >> phoneNumber;

    std::vector<Customer> results = customerController.findCustomerByMobile(phoneNumber);
    if (results.empty()) {
        std::cout << "No customers found with the given phone number." << std::endl;
    } else {
        for (auto customer : results) {
            std::cout << customer.toString() << std::endl;
        }
    }
}

void CustomerUI::findCustomerByName() {
    std::string surname;

    std::cout << "Enter Surname to search: ";
    std::cin >> surname;

    std::vector<Customer> results = customerController.findCustomersByName(surname);
    if (results.empty()) {
        std::cout << "No customers found with the given surname." << std::endl;
    } else {
        for (auto customer : results) {
            std::cout << customer.toString() << std::endl;
        }
    }
}

void CustomerUI::run() {
    int choice;
    do {
        printMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                deleteCustomer();
                break;
            case 3:
                updateCustomer();
                break;
            case 4:
                anonymizeCustomer();
                break;
            case 5:
                getAllCustomersSortedByName();
                break;
            case 6:
                std::cout << "Choose filter: " << std::endl;
                std::cout << "1. Find by name" << std::endl;
                std::cout << "2. Find by email" << std::endl;
                std::cout << "3. Find by mobile" << std::endl;
                std::cin >> choice;
                switch (choice) {
                    case 1:
                        findCustomerByName();
                        break;
                    case 2:
                        findCustomerByEmail();
                        break;
                    case 3:
                        findCustomerByMobile();
                        break;
                }
                break;
            case 0:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cerr << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0);
}