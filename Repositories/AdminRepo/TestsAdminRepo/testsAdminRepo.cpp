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

    repo.modify_admin("petre@gmail.com","is Active","false");
    repo.remove_admin("petre@gmail.com");
    assert(!repo.search_admin("petre@gmail.com"));

    repo.modify_admin("puscas@gmail.com","is Active","false");
    repo.remove_admin("puscas@gmail.com");
    assert(!repo.search_admin("puscas@gmail.com"));

    try {
        repo.remove_admin("puscas@gmail.com");
    }catch (const std::exception& e) {
        assert(std::string(e.what())=="Admin not found");
    }

    repo.add_admin(admin3);
    assert(repo.search_admin("puscas@gmail.com"));

    repo.modify_admin("puscas@gmail.com","is Active","false");
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
        if(adm["Email"]=="petre1@gmail.com") {
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

    Admin invalid_admin1("Radu", "Petre", "invalidemail.com", "manager", {14,2005,"june"}, "RP", 5000, "", "password123");
    try {
        repo.add_admin(invalid_admin1);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Invalid email format: invalidemail.com");
    }

    Admin invalid_admin2("Tincu", "Maria", "maria.tincue@example.com", "manager", {20,2000,"february"}, "TM", 50, "", "password123");
    try {
        repo.add_admin(invalid_admin2);
    } catch (const std::runtime_error& e) {
        assert(!(std::string(e.what()) == "Salary must be at least 100 EUR. Provided salary: 50"));
    }

    Admin valid_admin("Alesia", "Smaranda", "alesia.smaranda@example.com", "HR", {20,2000,"january"}, "AS", 1500, "", "password456");
    repo.add_admin(valid_admin);
    try {
        repo.modify_admin("alesia.smaranda@example.com", "Email", "invalidemail.com");
    } catch (const std::runtime_error& e) {
        assert((std::string(e.what()) == "Invalid email format: invalidemail.com"));
    }

    try {
        repo.modify_admin("alesia.smaranda@example.com", "Salary", "50");
    } catch (const std::runtime_error& e) {
        assert(!(std::string(e.what()) == "Salary must be at least 100 EUR. Provided salary: 50"));
    }
}

void run_tests_admin_repo() {
    test_verify_admin();
    test_modify_admin();
    tests_add_and_remove_admin();
    std::cout << "All AdminRepo tests finished successfully." << std::endl;
}