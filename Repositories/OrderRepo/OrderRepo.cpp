#include <iostream>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"
#include "OrderRepo.h"
#include <stdexcept>

using namespace std;

// Utility functions
std::string orderStatusToString(OrderStatus status) {
    switch (status) {
        case OrderStatus::Reservation: return "Reservation";
        case OrderStatus::Order: return "Order";
        case OrderStatus::Completed: return "Completed";
        default: throw std::runtime_error("Invalid OrderStatus.");
    }
}

OrderStatus stringToOrderStatus(const std::string& status) {
    if (status == "Reservation") return OrderStatus::Reservation;
    if (status == "Order") return OrderStatus::Order;
    if (status == "Completed") return OrderStatus::Completed;
    throw std::runtime_error("Invalid OrderStatus string.");
}

// Constructor
OrderRepo::OrderRepo(const std::string& filename) {
    this->filename = filename;
    this->read_from_file(this->filename);
}

// Public methods
json& OrderRepo::get_orders_json() {
    return this->orders;
}

void OrderRepo::add_order(const Order& order) {
    this->verify_order(order);

    json j;
    j["orderNumber"] = order.getOrderNumber();
    j["orderDate"] = order.getOrderDate();
    j["status"] = orderStatusToString(order.getStatus());
    j["car"] = order.getCar();
    j["start"] = order.getStart();
    j["end"] = order.getEnd();
    j["customer"] = order.getCustomer();
    j["employee"] = order.getEmployee();
    j["totalAmount"] = order.getTotalAmount();
    j["remark"] = (order.getRemark() != "") ? order.getRemark() : "";

    this->orders.push_back(j);
    this->write_to_file(this->filename);
}

void OrderRepo::remove_order(int orderNumber) {
    auto it = std::remove_if(this->orders.begin(), this->orders.end(),
                             [orderNumber](const json& orderJson) {
                                 return orderJson["orderNumber"] == orderNumber;
                             });

    if (it != this->orders.end()) {
        this->orders.erase(it, this->orders.end());
        this->write_to_file(this->filename);
        return;
    }
    throw runtime_error("Order with number: " + to_string(orderNumber) + " does not exist.");
}

void OrderRepo::modify_order(int orderNumber, const std::string& attribute, const std::string& value) {
    if (!this->search_order(orderNumber)) {
        throw runtime_error("Order with number: " + to_string(orderNumber) + " does not exist.");
    }

    for (auto& obj : this->orders) {
        if (obj["orderNumber"] == orderNumber) {
            if (attribute == "orderDate") {
                obj[attribute] = value;
            } else if (attribute == "status") {
                obj[attribute] = orderStatusToString(stringToOrderStatus(value));
            } else if (attribute == "car" || attribute == "start" || attribute == "end" ||
                       attribute == "customer" || attribute == "employee" || attribute == "remark") {
                obj[attribute] = value;
            } else if (attribute == "totalAmount") {
                obj[attribute] = std::stod(value);
            } else {
                throw runtime_error("Invalid attribute.");
            }
            break;
        }
    }
    this->write_to_file(this->filename);
}

bool OrderRepo::search_order(int orderNumber) const {
    for (const auto& obj : this->orders) {
        if (obj["orderNumber"] == orderNumber)
            return true;
    }
    return false;
}

// Private methods
void OrderRepo::write_to_file(std::string filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << this->orders.dump(4); // write array with indentation of 4 spaces
        file.close();
        return;
    }
    throw runtime_error("Error opening " + filename);
}

void OrderRepo::read_from_file(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return;
    }

    json j;
    file >> j; // read entire array from file

    if (j.is_array()) {
        for (const auto& orderJson : j) {
            this->orders.push_back(orderJson);
        }
    }
    file.close();
}

bool OrderRepo::verify_order(const Order& order) const {
    if (order.getOrderNumber() <= 0)
        throw runtime_error("Invalid Order Number.");
    if (order.getTotalAmount() < 0)
        throw runtime_error("Total Amount cannot be negative.");
    // Additional verifications can be added here
    return true;
}
