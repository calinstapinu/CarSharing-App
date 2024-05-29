#include <cassert>
#include "../AdminController.h"
#include "../Domain/Admin.h"
#include "../include/nlohmann/json.hpp"
#include <string>
#include <iostream>
#include <fstream>

void reset_test_environment() {
    std::ofstream ofs("AdminRepo/TestsAdminRepo/tests_Admin.json");
    ofs << "[]" << std::endl; // Reset the file with an empty JSON array
    ofs.close();
}

void test_create_admin() {
    reset_test_environment();
    AdminRepo repo("AdminRepo/TestsAdminRepo/tests_Admin.json");
    AdminController controller(repo);

    controller.createAdmin("Doe", "Cosmin", "cosmin.pilca@example.com", "Manager", "CP", {2, 1990, "January"}, 5000.0, "Remarks", true, "password");
    assert(repo.search_admin("cosmin.pilca@example.com"));
}

void test_update_admin() {
    reset_test_environment();
    AdminRepo repo("AdminRepo/TestsAdminRepo/tests_Admin.json");
    AdminController controller(repo);

    controller.createAdmin("Doe", "Cosmin", "cosmin.pilca@example.com", "Manager", "CP", {2, 1990, "January"}, 5000.0, "Remarks", true, "password");

    //std::cout << "Before update: " << repo.get_admin_json().dump(4) << std::endl;

    controller.updateAdmin("cosmin.pilca@example.com", "Position", "Supervisor");

    json admins = repo.get_admin_json();
    auto it = std::find_if(admins.begin(), admins.end(), [&](const json& adm) {
        return adm["Email"] == "cosmin.pilca@example.com";
    });
    //std::cout << "After update: " << repo.get_admin_json().dump(4) << std::endl;

    assert(it != admins.end() && (*it)["Position"] == "Supervisor");

    try {
        controller.updateAdmin("cosmin.pilca@example.com", "Email", "invalidemail.com");
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Invalid email format: invalidemail.com");
    }

    try {
        controller.updateAdmin("cosmin.pilca@example.com", "Salary", "50");
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Salary must be at least 100 EUR. Provided salary: 50.00");
    }
}


void test_delete_admin() {
    reset_test_environment();
    AdminRepo repo("AdminRepo/TestsAdminRepo/tests_Admin.json");
    AdminController controller(repo);

    controller.createAdmin("Doe", "Cosmin", "cosmin.pilca@example.com", "Manager", "CP", {2, 1990, "January"}, 5000.0, "Remarks", true, "password");

    //std::cout << "Created admin. Now deleting..." << std::endl;
    controller.deleteAdmin("cosmin.pilca@example.com");
    //std::cout << "Admin deleted. Verifying..." << std::endl;
    assert(!repo.search_admin("cosmin.pilca@example.com"));
    //std::cout << "Admin deletion verified." << std::endl;
}

void test_activate_admin() {
    reset_test_environment();
    AdminRepo repo("AdminRepo/TestsAdminRepo/tests_Admin.json");
    AdminController controller(repo);

    controller.createAdmin("Doe", "Cosmin", "cosmin.pilca@example.com", "Manager", "CP", {2, 1990, "January"}, 5000.0, "Remarks", false, "password");

    controller.activateAdmin("cosmin.pilca@example.com");
    json admins = repo.get_admin_json();
    auto it = std::find_if(admins.begin(), admins.end(), [&](const json& adm) {
        return adm["Email"] == "cosmin.pilca@example.com";
    });
    assert(it != admins.end() && (*it)["is Active"] == true);
}

void test_deactivate_admin() {
    reset_test_environment();
    AdminRepo repo("AdminRepo/TestsAdminRepo/tests_Admin.json");
    AdminController controller(repo);

    controller.createAdmin("Doe", "Cosmin", "cosmin.pilca@example.com", "Manager", "CP", {2, 1990, "January"}, 5000.0, "Remarks", true, "password");

    controller.deactivateAdmin("cosmin.pilca@example.com");
    json admins = repo.get_admin_json();
    auto it = std::find_if(admins.begin(), admins.end(), [&](const json& adm) {
        return adm["Email"] == "cosmin.pilca@example.com";
    });
    assert(it != admins.end() && (*it)["is Active"] == false);
}

void test_reset_admin_password() {
    reset_test_environment();
    AdminRepo repo("AdminRepo/TestsAdminRepo/tests_Admin.json");
    AdminController controller(repo);

    controller.createAdmin("Doe", "Cosmin", "cosmin.pilca@example.com", "Manager", "CP", {2, 1990, "January"}, 5000.0, "Remarks", true, "password");

    controller.resetAdminPassword("cosmin.pilca@example.com");
    json admins = repo.get_admin_json();
    auto it = std::find_if(admins.begin(), admins.end(), [&](const json& adm) {
        return adm["Email"] == "cosmin.pilca@example.com";
    });
    assert(it != admins.end() && (*it)["Password"] != "password");
}

void test_view_admin_salary() {
    reset_test_environment();
    AdminRepo repo("AdminRepo/TestsAdminRepo/tests_Admin.json");
    AdminController controller(repo);

    controller.createAdmin("Doe", "Cosmin", "cosmin.pilca@example.com", "Manager", "CP", {2, 1990, "January"}, 5000.0, "Remarks", true, "password");

    controller.viewAdminSalary("cosmin.pilca@example.com");
    json admins = repo.get_admin_json();
    auto it = std::find_if(admins.begin(), admins.end(), [&](const json& adm) {
        return adm["Email"] == "cosmin.pilca@example.com";
    });
    assert(it != admins.end() && (*it)["Salary"] == 5000.0);
}

void test_adjust_admin_salary() {
    reset_test_environment();
    AdminRepo repo("AdminRepo/TestsAdminRepo/tests_Admin.json");
    AdminController controller(repo);

    controller.createAdmin("Doe", "Cosmin", "cosmin.pilca@example.com", "Manager", "CP", {2, 1990, "January"}, 5000.0, "Remarks", true, "password");

    controller.adjustAdminSalary("cosmin.pilca@example.com", 6000.0);
    json admins = repo.get_admin_json();
    auto it = std::find_if(admins.begin(), admins.end(), [&](const json& adm) {
        return adm["Email"] == "cosmin.pilca@example.com";
    });
    assert(it != admins.end() && (*it)["Salary"] == 6000.0);
}

void test_search_admins_by_name() {
    reset_test_environment();
    AdminRepo repo("AdminRepo/TestsAdminRepo/tests_Admin.json");
    AdminController controller(repo);

    controller.createAdmin("Doe", "Cosmin", "cosmin.pilca@example.com", "Manager", "CP", {2, 1990, "January"}, 5000.0, "Remarks", true, "password");

    auto result = controller.searchAdminsByName("Cosmin");
    assert(result.size() == 1);
    assert(result[0].getFirstName() == "Cosmin");
}

void run_tests_admin_controller() {
    test_create_admin();
    test_update_admin();
    test_delete_admin();
    test_activate_admin();
    test_deactivate_admin();
    test_reset_admin_password();
    test_view_admin_salary();
    test_adjust_admin_salary();
    test_search_admins_by_name();
    std::cout << "All AdminController tests finished successfully." << std::endl;
}
