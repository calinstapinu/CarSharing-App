#include <cassert>
#include "TestsAdminRepo.h"
#include "../Domain/Admin.h"
#include "../include/nlohmann/json.hpp"
#include "../Repositories/AdminRepo/AdminRepo.h"
#include <string>
#include <iostream>

void tests_add_and_remove_admin() {
    AdminRepo repo("AdminRepo/TestsAdminRepo/tests_Admin.json");
    Admin admin1("Petre","Ioana","petre@gmail.com","manager",{12,2004,"june"},"PI",1200,"","password");
    Admin admin2("Petrea","Alexandra","petrea@gmail.com","senior manager",{13,2004,"june"},"PA",1205,"","password1");
    Admin admin3("Puscas","Andre","puscas@gmail.com","accountant",{15,2004,"june"},"PA",1210,"","password3");
    repo.add_admin(admin1);
    repo.add_admin(admin2);
    repo.add_admin(admin3);
    assert(repo.search_admin("petre@gmail.com"));
    assert(repo.search_admin("petrea@gmail.com"));
    assert(repo.search_admin("puscas@gmail.com"));
    repo.remove_admin("petre@gmail.com");
    assert(!repo.search_admin("petre@gmail.com"));
    repo.remove_admin("puscas@gmail.com");
    try {
        repo.remove_admin("puscas@gmail.com");
    }catch (const std::exception& e) {
        assert(std::string(e.what())=="Es existiert kein Amin mit diesem email");
    }
    repo.add_admin(admin3);
    assert(repo.search_admin("puscas@gmail.com"));
    repo.remove_admin("puscas@gmail.com");
    assert(!repo.search_admin("puscas@gmail.com"));
}

void test_modify_admin() {
    AdminRepo repo("AdminRepo/TestsAdminRepo/tests_Admin.json");
    Admin admin1("Petre","Ioana","petre@gmail.com","manager",{12,2004,"june"},"PI",1200,"","password");
    repo.add_admin(admin1);
    repo.modify_admin("petre@gmail.com","Position","senior manager");
    json admins=repo.get_admin_json();
    bool found=false;
    for(auto adm:admins) {
        if(adm["Email"]=="petre@gmail.com") {
            assert(adm["Position"]=="senior manager");
            found=true;
            break;
        }
    }
    assert(found);

    repo.modify_admin("petre@gmail.com","Password","password1");
    admins=repo.get_admin_json();
    found=false;
    for(auto adm:admins) {
        if(adm["Email"]=="petre@gmail.com") {
            assert(adm["Password"]=="password1");
            found=true;
            break;
        }
    }
    assert(found);

    repo.modify_admin("petre@gmail.com","Email","petre1@gmail.com");
    admins=repo.get_admin_json();
    found=false;
    for(auto adm:admins) {
        if(adm["Email"]=="petre@gmail.com") {
            assert(adm["Email"]=="petre1@gmail.com");
            found=true;
            break;
        }
    }
    assert(found);

    repo.modify_admin("petre1@gmail.com","Salary","2000");
    admins=repo.get_admin_json();
    found=false;
    for(auto adm:admins) {
        if(adm["Email"]=="petre1@gmail.com") {
            assert(adm["Salary"]==2000);
            found=true;
            break;
        }
    }
    assert(found);
}

void test_verify_admin() {
    AdminRepo repo("AdminRepo/TestsAdminRepo/tests_Admin.json");

    // Invalid email
    Admin invalid_admin1("John", "Doe", "invalidemail.com", "Manager", {14,2005,"june"}, "JD", 5000, "", "password123");
    try {
        repo.add_admin(invalid_admin1);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Invalid email format: invalidemail.com");
    }

    // Invalid salary
    Admin invalid_admin2("Jane", "Doe", "jane.doe@example.com", "Manager", {20,2000,"february"}, "JD", 50, "", "password123");
    try {
        repo.add_admin(invalid_admin2);
    } catch (const std::runtime_error& e) {
        assert(!(std::string(e.what()) == "Salary must be at least 100 EUR. Provided salary: 50"));
    }

    // Invalid modification to email
    Admin valid_admin("Alice", "Smith", "alice.smith@example.com", "HR", {20,2000,"january"}, "AS", 1500, "Notes", "password456");
    repo.add_admin(valid_admin);
    try {
        repo.modify_admin("AS", "Email", "invalidemail.com");
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Invalid email format: invalidemail.com");
    }

    // Invalid modification to salary
    try {
        repo.modify_admin("AS", "Salary", "50");
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Salary must be at least 100 EUR. Provided salary: 50");
    }

    // Trying to remove an active admin
    try {
        repo.remove_admin("AS");
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Cannot remove an active admin");
    }

    // Deactivate and then remove admin
    repo.modify_admin("AS", "Is Active", "false");
    try {
        repo.remove_admin("AS");
        assert(true);  // If no exception is thrown, the admin is removed successfully.
    } catch (const std::exception& e) {
        assert(false);  // Should not reach here.
    }

    // Trying to remove a non-existent admin
    try {
        repo.remove_admin("XYZ");
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Admin not found");
    }
}

void run_tests_admin_repo() {
    test_verify_admin();
    test_modify_admin();
    tests_add_and_remove_admin();
    std::cout << "All AdminRepo tests finished successfully." << std::endl;
}