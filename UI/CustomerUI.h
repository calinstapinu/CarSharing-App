//
// Created by ANDREI on 29/05/2024.
//

#ifndef JSON_TEST_CUSTOMERUI_H
#define JSON_TEST_CUSTOMERUI_H

#include "../Controllers/CustomerController/CustomerController.h"
#include <iostream>
#include <string>

class CustomerUI {
private:
    CustomerController customerController;

    void printMenu();
    void addCustomer();
    void deleteCustomer();
    void updateCustomer();
    void anonymizeCustomer();
    void listCustomer();
    void findCustomerByEmail();
    void findCustomerByMobile();
    void findCustomerByName();
    void getAllCustomersSortedByName();
    void run();

private:
    CustomerUI(std::string fileName) : customerController(fileName) {}


};

#endif //JSON_TEST_CUSTOMERUI_H