#include <cassert>
#include "../OrderController.h"
#include "../../../Domain/Order.h"
#include "../../../include/nlohmann/json.hpp"
#include <string>
#include <iostream>

void test_create_order() {
    OrderController controller("OrderRepo/TestsOrderRepo/tests.json");

    controller.createOrder(1, "2024-05-27", OrderStatus::Reservation, "Car1", "2024-06-01", "2024-06-10", "Customer1", "Employee1", 300, "Remark1", "employee");
    controller.createOrder(2, "2024-05-28", OrderStatus::Order, "Car2", "2024-06-05", "2024-06-12", "Customer2", "Employee2", 500, "Remark2", "admin");
    controller.createOrder(3, "2024-05-29", OrderStatus::Completed, "Car3", "2024-06-10", "2024-06-15", "Customer3", "Employee3", 450, "Remark3", "employee");

    assert(controller.searchOrder(1).getOrderNumber() == 1);
    assert(controller.searchOrder(2).getOrderNumber() == 2);
    assert(controller.searchOrder(3).getOrderNumber() == 3);

    controller.removeOrder(1, "employee", "Customer1");
    controller.removeOrder(2, "admin", "Customer2");
    controller.removeOrder(3, "employee", "Customer3");
}

void test_modify_order1() {
    OrderController controller("OrderRepo/TestsOrderRepo/tests.json");

    controller.createOrder(1, "2024-05-27", OrderStatus::Reservation, "Car1", "2024-06-01", "2024-06-10", "Customer1", "Employee1", 300, "Remark1", "employee");

    controller.modifyOrder(1, "remark", "UpdatedRemark", "Employee1", "employee");
    assert(controller.searchOrder(1).getRemark() == "UpdatedRemark");

    try {
        controller.modifyOrder(1, "totalAmount", "350", "Employee1", "employee");
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Completed orders cannot be modified.");
    }

    controller.modifyOrder(1, "totalAmount", "350", "Employee1", "employee");
    assert(controller.searchOrder(1).getTotalAmount() == 350);

    controller.removeOrder(1, "employee", "Customer1");

}

void test_remove_order1() {
    OrderController controller("OrderRepo/TestsOrderRepo/tests.json");

    controller.createOrder(1, "2024-05-27", OrderStatus::Reservation, "Car1", "2024-06-01", "2024-06-10", "Customer1", "Employee1", 300, "Remark1", "employee");

    controller.removeOrder(1, "employee", "Customer1");
    try {
        controller.searchOrder(1);
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Order with number: 1 does not exist.");
    }
}

void test_list_orders() {
    OrderController controller("OrderRepo/TestsOrderRepo/tests.json");

    controller.createOrder(1, "2024-05-27", OrderStatus::Reservation, "Car1", "2024-06-01", "2024-06-10", "Customer1", "Employee1", 300, "Remark1", "employee");
    controller.createOrder(2, "2024-05-28", OrderStatus::Order, "Car2", "2024-06-05", "2024-06-12", "Customer2", "Employee2", 500, "Remark2", "admin");
    controller.createOrder(3, "2024-05-29", OrderStatus::Completed, "Car3", "2024-06-10", "2024-06-15", "Customer3", "Employee3", 450, "Remark3", "employee");

    auto orders = controller.listOrders("2024-06-01", "2024-06-15");
    assert(orders.size() == 3);
    assert(orders[0].getTotalAmount() == 300);
    assert(orders[1].getTotalAmount() == 450);
    assert(orders[2].getTotalAmount() == 500);

    controller.removeOrder(1, "employee", "Customer1");
    controller.removeOrder(2, "admin", "Customer2");
    controller.removeOrder(3, "employee", "Customer3");
}

void test_calculate_total_sum() {
    OrderController controller("OrderRepo/TestsOrderRepo/tests.json");

    controller.createOrder(1, "2024-05-27", OrderStatus::Reservation, "Car1", "2024-06-01", "2024-06-10", "Customer1", "Employee1", 300, "Remark1", "employee");
    controller.createOrder(2, "2024-05-28", OrderStatus::Order, "Car2", "2024-06-05", "2024-06-12", "Customer2", "Employee2", 500, "Remark2", "admin");
    controller.createOrder(3, "2024-05-29", OrderStatus::Completed, "Car3", "2024-06-10", "2024-06-15", "Customer3", "Employee3", 450, "Remark3", "employee");

    double totalSum = controller.calculateTotalSum("month", "2024-05");
    assert(totalSum == 1250);

    controller.removeOrder(1, "employee", "Customer1");
    controller.removeOrder(2, "admin", "Customer2");
    controller.removeOrder(3, "employee", "Customer3");
}

void run_tests_order_controller() {
    test_create_order();
    test_modify_order1();
    test_remove_order1();
    test_list_orders();
    test_calculate_total_sum();
    std::cout << "All OrderController tests finished successfully." << std::endl;
}
