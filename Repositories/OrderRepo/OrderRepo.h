#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "nlohmann/json.hpp"
#include "../../Domain/Order.h"

using json = nlohmann::json;

// Declare conversion functions as inline to avoid multiple definitions
inline std::string orderStatusToString(OrderStatus status) {
    switch (status) {
        case OrderStatus::Reservation: return "Reservation";
        case OrderStatus::Order: return "Order";
        case OrderStatus::Completed: return "Completed";
        default: return "Unknown";
    }
}

inline OrderStatus stringToOrderStatus(const std::string& status) {
    if (status == "Reservation") return OrderStatus::Reservation;
    if (status == "Order") return OrderStatus::Order;
    if (status == "Completed") return OrderStatus::Completed;
    throw std::runtime_error("Invalid OrderStatus string.");
}

class OrderRepo {
private:
    json orders; // JSON array to store orders
    std::string filename; // Filename to read/write orders

    /// Reads orders from the file specified by filename
    void read_from_file(const std::string& filename);

    /// Writes orders to the file specified by filename
    void write_to_file(std::string filename);

    /// Verifies all aspects of an order before adding it
    bool verify_order(const Order& order) const;

    /// Saves the current state of orders to the file
    void save();

public:
    /// Constructor that initializes the repository with a given filename
    OrderRepo(const std::string& filename);

    /// Returns a reference to the JSON array of orders
    /// You can access elements in a loop: e.g., order["orderNumber"]
    /// Make sure to use quotes and match the fields in the OrderRepo.cpp - add function
    json& get_orders_json();

    /// Adds an order object to the JSON array of orders
    /// All properties of the order are verified before adding
    /// If something is incorrect, exceptions are thrown and need to be caught with TRY and CATCH
    /// used in Controller / UI
    void add_order(const Order& order);

    /// Removes an order from the array of orders
    /// Takes an integer parameter corresponding to an existing order number
    /// If no order with that number exists, an exception is thrown
    /// If the order was removed successfully, no exception is thrown
    void remove_order(int orderNumber);

    /// Modifies an attribute of an order
    /// Parameters: 1. orderNumber (unique for each order)
    /// 2. attribute should be a string with one of the parameters:
    /// orderNumber, orderDate, status, car, startDate, endDate, customer, employee,
    /// totalAmount, remark - ONLY THESE ARE VALID (can be written in any way, as they are converted to the correct format in the function)
    /// 3. value => should be a valid value for the modified attribute
    void modify_order(int orderNumber, const std::string& attribute, const std::string& value);

    /// Returns true if an order with the given order number exists, false otherwise
    bool search_order(int orderNumber) const;
};
