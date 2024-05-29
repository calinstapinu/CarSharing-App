#include <cassert>
#include "../CustomerRepo.h"
#include "../Domain/Customer.h"
#include <iostream>

using namespace std;

void test_add_customer() {
    try {
        CustomerRepo repo("CustomerRepo/TestsCustomerRepo/customers.json");
        Customer customer1("1", "Doe", "John", "john@example.com", "+123456789", "123 Street, City", "Regular customer", "password123", false);
        Customer customer2("2", "Smith", "Alice", "alice@example.com", "+987654321", "456 Avenue, Town", "VIP customer", "securepass", false);

        repo.createCustomer(customer1);
        repo.createCustomer(customer2);


        repo.removeCustomer("john@example.com");
        repo.removeCustomer("alice@example.com");

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        assert(false); // Test failed if an exception is caught
    }
}

void test_remove_customer() {
    try {
        CustomerRepo repo("CustomerRepo/TestsCustomerRepo/customers.json");
        Customer customer("1", "Doe", "John", "john@example.com", "+123456789", "123 Street, City", "Regular customer", "password123", false);

        repo.createCustomer(customer);
        assert(repo.searchAfterEmail("john@example.com").getEmail() == "john@example.com");

        repo.removeCustomer("john@example.com");
        assert(repo.searchAfterEmail("john@example.com").getId() == "0");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        assert(false); // Test failed if an exception is caught
    }
}

void test_modify_customer() {
    try {
        CustomerRepo repo("CustomerRepo/TestsCustomerRepo/customers.json");
        Customer customer("1", "Doe", "John", "john@example.com", "+123456789", "123 Street, City", "Regular customer", "password123", false);

        repo.createCustomer(customer);
        assert(repo.searchAfterEmail("john@example.com").getLastName() == "Doe");

        repo.modifyCustomer("john@example.com", "lastName", "Smith");
        assert(repo.searchAfterEmail("john@example.com").getLastName() == "Smith");

        repo.removeCustomer("john@example.com");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        assert(false); // Test failed if an exception is caught
    }
}

void test_search_customer() {
    try {
        CustomerRepo repo("CustomerRepo/TestsCustomerRepo/customers.json");
        Customer customer1("1", "Doe", "John", "john@example.com", "+123456789", "123 Street, City", "Regular customer", "password123", false);
        Customer customer2("2", "Smith", "Alice", "alice@example.com", "+987654321", "456 Avenue, Town", "VIP customer", "securepass", false);

        repo.createCustomer(customer1);
        repo.createCustomer(customer2);

        assert(repo.searchAfterEmail("john@example.com").getLastName() == "Doe");
        assert(repo.searchAfterMobile("+987654321").getLastName() == "Smith");

        std::vector<Customer> searchResults = repo.searchAfterName("Alice");
        assert(searchResults.size() == 1);
        assert(searchResults[0].getEmail() == "alice@example.com");

        repo.removeCustomer("john@example.com");
        repo.removeCustomer("alice@example.com");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        assert(false); // Test failed if an exception is caught
    }
}

void run_tests_customer_repo() {
    test_add_customer();
    test_remove_customer();
    test_modify_customer();
    test_search_customer();
    std::cout << "All CustomerRepo tests finished successfully." << std::endl;
}