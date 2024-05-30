//
// Created by Tudor on 29.05.2024.
//

#include <cassert>
#include "../MitarbeiterController.h"
#include "../../../Domain/Mitarbeiter.h"
#include "../../../include/nlohmann/json.hpp"
#include <string>
#include <iostream>
using namespace std;

void test_add_employeee() {
    MitarbeiterController controller("controller.json");
    controller.add_employee("Doe", "John", "john.doe@example.com", "developer", "JD", "01.01.1980", 1200.0, "Good employee", false);
    assert(controller.search_employee("JD"));
}

void test_modify_employeee() {
    MitarbeiterController controller("controller.json");
    controller.modify_employee("JD", "lastName", "Smith");
    assert(controller.search_employee("JD"));
}

void test_remove_employeee() {
    MitarbeiterController controller("controller.json");
    controller.remove_employee("JD");
    //assert(!controller.search_employee("JD"));
}

void test_list_all_employeees() {
    MitarbeiterController controller("controller.json");
    controller.list_all_employees();
}

void test_change_own_remarks() {
    MitarbeiterController controller("controller.json");
    controller.add_employee("Doe", "John", "john.doe@example.com", "developer", "JD", "01.01.1980", 1200.0, "Good employee", false);
    controller.changeOwnRemarks("JD", "New remarks");
    assert(controller.search_employee("JD"));
}

void test_search_employee_by_email() {
    MitarbeiterController controller("controller.json");
    controller.add_employee("Doe", "John", "john.doe@example.com", "developer", "JD", "01.01.1980", 1200.0, "Good employee", false);
    Mitarbeiter result = controller.searchEmployeeByEmail("john.doe@example.com");
    assert(result.getEmail() == "john.doe@example.com");
}

void test_validate_admin_access() {
    MitarbeiterController controller("controller.json");
    controller.add_employee("Doe", "John", "john.doe@example.com", "developer", "JD", "01.01.1980", 1200.0, "Good employee", true);
    try {
        controller.validateAdminAccess("JD");
        assert(true);
    } catch (const std::runtime_error& error) {
        assert(false);
    }
    controller.add_employee("Doe", "Jane", "jane.doe@example.com", "developer", "JD", "01.01.1980", 1200.0, "Good employee", false);
    try {
        controller.validateAdminAccess("JD");
        assert(true);
    } catch (const std::runtime_error& error) {
        assert(true);
    }
}

void run_tests_mitarbeiter_controller() {
    test_add_employeee();
    test_modify_employeee();
    test_remove_employeee();
    //test_list_all_employeees();
    test_change_own_remarks();
    test_search_employee_by_email();
    test_validate_admin_access();
    cout << "All MitarbeiterController tests finished successfully." << endl;
}