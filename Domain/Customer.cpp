#include "Customer.h"

Customer::Customer(std::string id, std::string lastName, std::string firstName, std::string email,
                   std::string mobile, std::string address, std::string remarks, std::string password, bool gdprDeleted)
        : id(id), lastName(lastName), firstName(firstName), email(email),
          mobile(mobile), address(address), remarks(remarks), password(password), gdprDeleted(gdprDeleted) {}

void Customer::anonymize() {
    lastName = "Kunde-" + id;
    firstName = "Unbekannt";
    email = "";
    mobile = "";
    address = "";
    remarks = "";
    gdprDeleted = true;
}