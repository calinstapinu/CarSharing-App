#ifndef JSON_TEST_CUSTOMERCONTROLLER_H
#define JSON_TEST_CUSTOMERCONTROLLER_H

#include "../../Repositories/CustomerRepo/CustomerRepo.h"
#include <vector>
#include <string>

class CustomerController {
private:
    CustomerRepo customerRepo;

public:
    CustomerController(const std::string& filename);

    void addCustomer(const Customer& customer);
    bool deleteCustomer(const std::string& email); // Return type changed to bool to handle deletion checks
    void updateCustomer(const std::string& email, const std::string& attribute, const std::string& value);
    void anonymizeCustomer(const std::string& email);
    std::vector<Customer> getAllCustomersSortedByName();
    Customer findCustomerByEmail(const std::string& email);
    Customer findCustomerByMobile(const std::string& mobile);
    std::vector<Customer> findCustomersByName(const std::string& name);
};

#endif // JSON_TEST_CUSTOMERCONTROLLER_H