#include <cassert>
#include <iostream>
#include "../OrderRepo.h"
#include "../../../Domain/Order.h"
#include "../../../include/nlohmann/json.hpp"
#include <string>

void test_add_order() {
    std::cout << "Starting test_add_order..." << std::endl;
    OrderRepo repo("OrderRepo/TestsOrderRepo/tests.json");
    Order order1(1, "2024-05-27", OrderStatus::Reservation, "Car1", "2024-06-01", "2024-06-10", "Customer1", "Employee1", 300, "Remark1");
    Order order2(2, "2024-05-28", OrderStatus::Order, "Car2", "2024-06-05", "2024-06-12", "Customer2", "Employee2", 500, "Remark2");
    Order order3(3, "2024-05-29", OrderStatus::Completed, "Car3", "2024-06-10", "2024-06-15", "Customer3", "Employee3", 450, "Remark3");

    repo.add_order(order1);
    repo.add_order(order2);
    repo.add_order(order3);

    assert(repo.search_order(1));
    assert(repo.search_order(2));
    assert(repo.search_order(3));

    repo.remove_order(1);
    repo.remove_order(2);
    repo.remove_order(3);
    assert(!repo.search_order(1));
    assert(!repo.search_order(2));
    assert(!repo.search_order(3));
    std::cout << "test_add_order finished successfully." << std::endl;
}

void test_remove_order() {
    std::cout << "Starting test_remove_order..." << std::endl;
    OrderRepo repo("OrderRepo/TestsOrderRepo/tests.json");
    Order order(1, "2024-05-27", OrderStatus::Reservation, "Car1", "2024-06-01", "2024-06-10", "Customer1", "Employee1", 300, "Remark1");

    repo.add_order(order);

    repo.remove_order(1);
    assert(!repo.search_order(1));

    try {
        repo.remove_order(99);
    } catch (const std::exception& e) {
        assert(std::string(e.what()) == "Order with number: 99 does not exist.");
    }

    Order order2(2, "2024-05-28", OrderStatus::Order, "Car2", "2024-06-05", "2024-06-12", "Customer2", "Employee2", 500, "Remark2");
    Order order3(3, "2024-05-29", OrderStatus::Completed, "Car3", "2024-06-10", "2024-06-15", "Customer3", "Employee3", 450, "Remark3");
    repo.add_order(order2);
    repo.add_order(order3);

    repo.remove_order(2);
    assert(!repo.search_order(2));

    try {
        repo.remove_order(99);
    } catch (const std::exception& e) {
        assert(std::string(e.what()) == "Order with number: 99 does not exist.");
    }

    repo.remove_order(3);
    assert(!repo.search_order(3));
    std::cout << "test_remove_order finished successfully." << std::endl;
}

void test_modify_order() {
    std::cout << "Starting test_modify_order..." << std::endl;
    OrderRepo repo("OrderRepo/TestsOrderRepo/tests.json");
    Order order(1, "2024-05-27", OrderStatus::Reservation, "Car1", "2024-06-01", "2024-06-10", "Customer1", "Employee1", 300, "Remark1");

    repo.add_order(order);

    repo.modify_order(1, "remark", "UpdatedRemark");
    json orders = repo.get_orders_json();
    bool found = false;
    for (auto obj : orders) {
        if (obj["orderNumber"] == 1) {
            assert(obj["remark"] == "UpdatedRemark");
            found = true;
            break;
        }
    }
    assert(found);

    repo.modify_order(1, "status", "Completed");
    orders = repo.get_orders_json();
    found = false;
    for (auto obj : orders) {
        if (obj["orderNumber"] == 1) {
            assert(obj["status"] == "Completed");
            found = true;
            break;
        }
    }
    assert(found);

    repo.modify_order(1, "totalAmount", "350");
    orders = repo.get_orders_json();
    found = false;
    for (auto obj : orders) {
        if (obj["orderNumber"] == 1) {
            assert(obj["totalAmount"] == 350);
            found = true;
            break;
        }
    }
    assert(found);

    repo.remove_order(1);
    std::cout << "test_modify_order finished successfully." << std::endl;
}

void test_verify_order() {
    std::cout << "Starting test_verify_order..." << std::endl;
    OrderRepo repo("OrderRepo/TestsOrderRepo/tests.json");

    Order invalid_order(0, "2024-05-27", OrderStatus::Reservation, "Car1", "2024-06-01", "2024-06-10", "Customer1", "Employee1", 300, "Remark1");
    try {
        repo.add_order(invalid_order);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Invalid Order Number.");
    }

    Order invalid_order2(1, "2024-05-27", OrderStatus::Reservation, "Car1", "2024-06-01", "2024-06-10", "Customer1", "Employee1", -300, "Remark1");
    try {
        repo.add_order(invalid_order2);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Total Amount cannot be negative.");
    }

    Order valid_order(1, "2024-05-27", OrderStatus::Reservation, "Car1", "2024-06-01", "2024-06-10", "Customer1", "Employee1", 300, "Remark1");
    repo.add_order(valid_order);
    assert(repo.search_order(1));

    repo.remove_order(1);
    std::cout << "test_verify_order finished successfully." << std::endl;
}

void run_tests_order_repo() {
    std::cout << "Starting OrderRepo tests..." << std::endl;
    test_add_order();
    test_remove_order();
    test_modify_order();
    test_verify_order();
    std::cout << "All OrderRepo tests finished successfully." << std::endl;
}
