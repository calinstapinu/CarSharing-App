#include <cassert>
#include "../AutoRepo.h"
#include "../../../Domain/Auto.h"
#include "../../../include/nlohmann/json.hpp"
#include <string>


void test_add_car() {
    AutoRepo repo("AutoRepo/TestsAutoRepo/tests.json");
    Auto car("ABC123", "ModelX", "Tesla", 2023, 10000, 200, "Electric", "Automatik", "Black");
    Auto car2("AFF245", "ModelX", "Tesla", 2023, 10000, 200, "Electric", "Automatik", "Black", "Damaged");
    Auto car3("AFF246", "ModelX", "Tesla", 2023, 555, 200, "Electric", "Automatik", "Black", "Damaged");

    repo.add_car(car);
    repo.add_car(car2);
    repo.add_car(car3);

    assert(repo.search_car("ABC123"));
    assert(repo.search_car("AFF245"));
    assert(repo.search_car("AFF246"));

    repo.remove_car("ABC123");
    repo.remove_car("AFF245");
    repo.remove_car("AFF246");
    assert(!repo.search_car("ABC123"));
    assert(!repo.search_car("AFF245"));
    assert(!repo.search_car("AFF246"));
}

void test_remove_car() {
    AutoRepo repo("AutoRepo/TestsAutoRepo/tests.json");
    Auto car("ABC123", "ModelX", "Tesla", 2023, 10000, 200, "Electric", "Automatik", "Black");

    repo.add_car(car);

    repo.remove_car("ABC123");
    assert(!repo.search_car("ABC123"));

    try {
        repo.remove_car("XYZ789");
    } catch (const std::exception& e) {
        assert(std::string(e.what()) == "Auto mit Kennzeichen: XYZ789 existiert nicht oder hat eine aktive Bestellung.");
    }

    Auto car2("DEF456", "ModelY", "BMW", 2022, 20000, 150, "Benzin", "Automatik", "Blue");
    Auto car3("GHI789", "ModelZ", "Audi", 2021, 30000, 180, "Diesel", "Automatik", "Red");
    repo.add_car(car2);
    repo.add_car(car3);

    repo.remove_car("DEF456");
    assert(!repo.search_car("DEF456"));

    try {
        repo.remove_car("XYZ000");
    } catch (const std::exception& e) {
        assert(std::string(e.what()) == "Auto mit Kennzeichen: XYZ000 existiert nicht oder hat eine aktive Bestellung.");
    }

    repo.remove_car("GHI789");
    assert(!repo.search_car("GHI789"));
}

void test_modify_car1() {
    AutoRepo repo("AutoRepo/TestsAutoRepo/tests.json");
    Auto car("ABC123", "ModelX", "Tesla", 2023, 10000, 200, "Electric", "Automatik", "Black");

    repo.add_car(car);

    repo.modify_car("ABC123", "farbe", "White");

    json cars = repo.get_cars_json();
    bool found = false;
    for (auto obj : cars) {
        if (obj["kennzeichen"] == "ABC123") {
            assert(obj["farbe"] == "White");
            found = true;
            break;
        }
    }
    assert(found);

    repo.modify_car("ABC123", "modell", "ModelY");

    cars = repo.get_cars_json();
    found = false;
    for (auto obj : cars) {
        if (obj["kennzeichen"] == "ABC123") {
            assert(obj["modell"] == "ModelY");
            found = true;
            break;
        }
    }
    assert(found);
    repo.modify_car("ABC123", "erstzulassungsjahr", "2022");

    cars = repo.get_cars_json();
    found = false;
    for (auto obj : cars) {
        if (obj["kennzeichen"] == "ABC123") {
            assert(obj["erstzulassungsjahr"] == 2022);
            found = true;
            break;
        }
    }
    assert(found);
    repo.remove_car("ABC123");
}

void test_modify_car2() {
    AutoRepo repo("AutoRepo/TestsAutoRepo/tests.json");
    Auto car("ABC123", "ModelX", "Tesla", 2023, 10000, 200, "Electric", "Automatik", "Black");

    repo.add_car(car);
    repo.modify_car("ABC123", "farbe", "White");

    json cars = repo.get_cars_json();
    bool found = false;
    for (auto obj : cars) {
        if (obj["kennzeichen"] == "ABC123") {
            assert(obj["farbe"] == "White");
            found = true;
            break;
        }
    }
    assert(found);

    repo.modify_car("ABC123", "aktiv", "nein");

    cars = repo.get_cars_json();
    found = false;
    for (auto obj : cars) {
        if (obj["kennzeichen"] == "ABC123") {
            assert(obj["aktiv"] == "nein");
            found = true;
            break;
        }
    }
    assert(found);

    try {
        repo.modify_car("ABC123", "aktiv", "ja");
    } catch (const std::exception& e) {
        assert(std::string(e.what()) == "Verboten. Man darf nicht das Auto ABC123 deaktivieren, weil es eine aktive Bestellung hat.");
    }

    repo.remove_car("ABC123");
}


void test_verify_car() {
    AutoRepo repo("AutoRepo/TestsAutoRepo/tests.json");

    Auto invalid_car("", "ModelX", "Tesla", 2023, 10000, 200, "Electric", "Automatik", "Black");
    try {
        repo.add_car(invalid_car);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Invalid Kennzeichen.");
    }

    Auto invalid_car2("AF#$%", "ModelX", "Tesla", 2023, 10000, 200, "Electric", "Automatik", "Black");
    try {
        repo.add_car(invalid_car2);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Invalid Kennzeichen.");
    }

    Auto invalid_car3("ABC245", "ModelX", "Tesla", 2025, 10000, 200, "Electric", "Automatik", "Black");
    try {
        repo.add_car(invalid_car3);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Ersatzlassungsjahr soll zwischen 2000 und 2024 sein.");
    }

    Auto invalid_car4("ABC245", "ModelX", "Tesla", 1990, 10000, 200, "Electric", "Automatik", "Black");
    try {
        repo.add_car(invalid_car4);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Ersatzlassungsjahr soll zwischen 2000 und 2024 sein.");
    }

    Auto invalid_car5("ABC245", "ModelX", "Tesla", 2021, -100, 200, "Electric", "Automatik", "Black");
    try {
        repo.add_car(invalid_car5);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Kilometerstand darf nicht negativ sein");
    }

    Auto invalid_car6("ABC245", "ModelX", "Tesla", 2021, 100, -200, "Electric", "Automatik", "Black");
    try {
        repo.add_car(invalid_car6);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Tagespreis kann nicht kleiner als Null sein.");
    }

    Auto invalid_car7("ABC245", "ModelX", "Tesla", 2021, 100, 200, "Honig", "Automatik", "Black");
    try {
        repo.add_car(invalid_car7);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Invalid Kraftstoffart: Diesel/Benzin/Electric/Gas");
    }

    Auto invalid_car8("ABC245", "ModelX", "Tesla", 2021, 100, 200, "Benzin", "SemiAuto", "Black");
    try {
        repo.add_car(invalid_car8);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Invalid Getriebe: Automatik/Schaltgetriebe");
    }

    try {
        repo.remove_car("ABC123");
    } catch (const std::exception& e) {
        assert(true);
        assert(std::string(e.what()) == "Auto mit Kennzeichen: ABC123 existiert nicht oder hat eine aktive Bestellung.");
    }
}

void run_tests_auto_repo(){
    test_add_car();
    test_remove_car();
    test_modify_car1();
    test_modify_car2();
    test_verify_car();
}