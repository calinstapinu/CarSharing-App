#include "OrderController.h"
#include <algorithm>
#include <stdexcept>

OrderController::OrderController(const std::string& filename) : orderRepo(filename) {}

void OrderController::createOrder(int ordNum, const std::string& ordDate, OrderStatus status, const std::string& car,
                                  const std::string& start, const std::string& end, const std::string& cust,
                                  const std::string& emp, double totalAmt, const std::string& rem, const std::string& userType) {
    if (userType != "employee" && userType != "admin") {
        throw std::runtime_error("Only employees or admins can create orders.");
    }

    Order newOrder(ordNum, ordDate, status, car, start, end, cust, emp, totalAmt, rem);
    this->validateOrder(newOrder);
    orderRepo.add_order(newOrder);
}

void OrderController::modifyOrder(int ordNum, const std::string& attribute, const std::string& value, const std::string& emp, const std::string& userType) {
    if (userType != "employee" && userType != "admin") {
        throw std::runtime_error("Only employees or admins can modify orders.");
    }

    Order order = searchOrder(ordNum);

    if (order.getStatus() == OrderStatus::Completed) {
        throw std::runtime_error("Completed orders cannot be modified.");
    }

    if (userType == "employee" && order.getEmployee() != emp) {
        throw std::runtime_error("Employees can only modify their own orders.");
    }

    orderRepo.modify_order(ordNum, attribute, value);
}

void OrderController::removeOrder(int ordNum, const std::string& userType, const std::string& cust) {
    Order order = searchOrder(ordNum);

    if (userType == "customer" && order.getCustomer() != cust) {
        throw std::runtime_error("Customers can only delete their own orders.");
    }

    orderRepo.remove_order(ordNum);
}

std::vector<Order> OrderController::listOrders(const std::string& startDate, const std::string& endDate) {
    std::vector<Order> result;
    auto ordersJson = orderRepo.get_orders_json();

    for (const auto& orderJson : ordersJson) {
        Order order(
                orderJson["orderNumber"],
                orderJson["orderDate"],
                stringToOrderStatus(orderJson["status"]),
                orderJson["car"],
                orderJson["start"],
                orderJson["end"],
                orderJson["customer"],
                orderJson["employee"],
                orderJson["totalAmount"],
                orderJson["remark"]
        );

        if (order.getStart() >= startDate && order.getEnd() <= endDate) {
            result.push_back(order);
        }
    }

    std::sort(result.begin(), result.end(), [](const Order& a, const Order& b) {
        return a.getTotalAmount() < b.getTotalAmount();
    });

    return result;
}

Order OrderController::searchOrder(int ordNum) {
    auto ordersJson = orderRepo.get_orders_json();

    for (const auto& orderJson : ordersJson) {
        if (orderJson["orderNumber"] == ordNum) {
            return Order(
                    orderJson["orderNumber"],
                    orderJson["orderDate"],
                    stringToOrderStatus(orderJson["status"]),
                    orderJson["car"],
                    orderJson["start"],
                    orderJson["end"],
                    orderJson["customer"],
                    orderJson["employee"],
                    orderJson["totalAmount"],
                    orderJson["remark"]
            );
        }
    }

    throw std::runtime_error("Order with number: " + std::to_string(ordNum) + " does not exist.");
}

double OrderController::calculateTotalSum(const std::string& period, const std::string& periodValue) {
    double totalSum = 0.0;
    auto ordersJson = orderRepo.get_orders_json();

    for (const auto& orderJson : ordersJson) {
        std::string orderDate = orderJson["orderDate"].get<std::string>();
        if (orderDate.substr(0, periodValue.length()) == periodValue) {
            totalSum += orderJson["totalAmount"].get<double>();
        }
    }

    return totalSum;
}

void OrderController::validateOrder(const Order& order) {
    if (orderRepo.search_order(order.getOrderNumber())) {
        throw std::runtime_error("Order number must be unique.");
    }

    if (order.getStart() > order.getEnd()) {
        throw std::runtime_error("Order start date cannot be after the end date.");
    }

    auto ordersJson = orderRepo.get_orders_json();
    for (const auto& orderJson : ordersJson) {
        if (orderJson["car"] == order.getCar()) {
            if (!(order.getEnd() < orderJson["start"] || order.getStart() > orderJson["end"])) {
                throw std::runtime_error("Overlapping reservations/orders for the same car are not allowed.");
            }
        }
    }

    int reservationCount = 0;
    for (const auto& orderJson : ordersJson) {
        if (orderJson["customer"] == order.getCustomer() && orderJson["status"] == "Reservation") {
            reservationCount++;
        }
    }
    if (reservationCount >= 5) {
        throw std::runtime_error("A customer cannot have more than 5 reservations.");
    }

    if (order.getOrderNumber() <= 0) {
        throw std::runtime_error("Invalid Order Number.");
    }

    if (order.getTotalAmount() < 0) {
        throw std::runtime_error("Total Amount cannot be negative.");
    }

    if (order.getCustomer() != "" && order.getEmployee() == "") {
        throw std::runtime_error("Employee must not be empty for reservations created by employees.");
    }
}
