#include <cassert>
#include "../MitarbeiterRepo.h"
#include "../../../Domain/Mitarbeiter.h"
//#include "../../../include/nlohmann/json.hpp"
#include <string>
#include <iostream>
using namespace std;

void test_add_employee() {
    MitarbeiterRepo repo("AutoRepo/TestsAutoRepo/tests.json");
    Mitarbeiter employee("Mustermann", "Max", "max.mustermann@test.de", "Verkäufer", "MM", "03.07.1990", 2100,"bla","yes");
    Mitarbeiter employee1("Herz", "Kathrin", "herz.kathrin@test.de", "Verkäufer", "HK", "01.05.2004",3800,"da","nein");
    Mitarbeiter employee3("Korn", "Max", "max.korn@test.de", "Verkäufer", "KM", "22.02.2000", 2000, "blabla","yes");

    repo.add_employee(employee);
    repo.add_employee(employee1);
    repo.add_employee(employee3);

    assert(repo.search_employee("MM"));
    assert(repo.search_employee("HK"));
    assert(repo.search_employee("KM"));
    assert(!repo.search_employee("ALE"));


}
void test_remove_employee() {
    MitarbeiterRepo repo("MitarbeiterRepo/TestsMitarbeiterRepo/tests.json");
    Mitarbeiter employee("Mustermann", "Max", "max.mustermann@test.de", "Verkäufer", "MM", "03.07.1990", 2100,"bla","yes");
    employee.setActive(false);
    repo.add_employee(employee);
    repo.remove_employee("MM");
    assert(!repo.search_employee("MM"));


    Mitarbeiter employee1("Herz", "Kathrin", "herz.kathrin@test.de", "Verkäufer", "HK", "01.05.2004",3800,"da","nein");
    Mitarbeiter employee3("Korn", "Max", "max.korn@test.de", "Verkäufer", "KM", "22.02.2000", 2000, "blabla","yes");
    repo.add_employee(employee1);
    repo.add_employee(employee3);
    repo.remove_employee("HK");

    assert(!repo.search_employee("HK"));
}

void test_modify_employee1() {
    MitarbeiterRepo repo("MitarbeiterRepo/TestsMitarbeiterRepo/tests.json");
    Mitarbeiter employee("Mustermann", "Max", "max.mustermann@test.de", "Verkäufer", "MM", "03.07.1990", 2100, "bla", true);
    repo.add_employee(employee);

    // Modifică salariul angajatului
    repo.modify_employee("MM", "salary", "3500");

    // Verifică modificarea
    json employees = repo.get_mitarbeiter_json();
    bool found = false;
    for (const auto& obj : employees) {
        if (obj["abbreviation"] == "MM") {
            assert(obj["salary"] == 3500);
            found = true;
            break;
        }
    }
    assert(found);

    // Adaugă un alt angajat pentru teste suplimentare
    Mitarbeiter employee2("Pop", "Maria", "maria.pop@test.de", "Manager", "PM", "01.01.1985", 3000, "remarks", true);
    repo.add_employee(employee2);

    // Modifică abrevierea angajatului
    repo.modify_employee("PM", "position", "Senior Manager");

    // Verifică modificarea
    employees = repo.get_mitarbeiter_json();
    found = false;
    for (const auto& obj : employees) {
        if (obj["abbreviation"] == "PM") {
            assert(obj["position"] == "Senior Manager");
            found = true;
            break;
        }
    }
    assert(found);

    // Modifică anul de înmatriculare al unei mașini
    repo.modify_employee("MM", "birthDate", "01.01.2000");

    // Verifică modificarea
    employees = repo.get_mitarbeiter_json();
    found = false;
    for (const auto& obj : employees) {
        if (obj["abbreviation"] == "MM") {
            assert(obj["birthDate"] == "01.01.2000");
            found = true;
            break;
        }
    }
    assert(found);

    // Șterge angajatul
    repo.remove_employee("MM");

    // Verifică ștergerea
    employees = repo.get_mitarbeiter_json();
    found = false;
    for (const auto& obj : employees) {
        if (obj["abbreviation"] == "MM") {
            found = true;
            break;
        }
    }
    assert(!found); // Trebuie să fie false, deoarece angajatul a fost șters
}


void test_verify_employee() {
    MitarbeiterRepo repo("MitarbeiterRepo/TestsMitarbeiterRepo/tests.json");

    Mitarbeiter invalid_employee("Pop", "Maria", "maria.pop@test.de", "Manager", "PM", "01.01.1700", 3000, "remarks", true);

    try {
        repo.add_employee(invalid_employee);
    } catch (const std::runtime_error& e) {;
        assert(std::string(e.what()) == "Invalid year of birth.");
    }

    //Mitarbeiter invalid_employee2("Pop", "Maria", "maria.pop@test.de", "Manager", "PM", "01.01.1985", 30, "remarks", true);


}


void run_tests_mitarbeiter_repo(){
    test_add_employee();
    test_remove_employee();
    test_modify_employee1();
    test_verify_employee();
    std::cout << "All MitarbeiterRepo tests finished successfully." << std::endl;
}
