#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "nlohmann/json.hpp"
#include "../../Domain/Order.h"

using json = nlohmann::json;

class OrderRepo {
private:
    json orders;
    std::string filename;

    void read_from_file(const std::string& filename);

    void write_to_file(std::string filename);

    bool verify_order(const Order& order) const;

    void save();

public:
    OrderRepo(const std::string& filename);

    json& get_orders_json();

    void add_order(const Order& order);

    void remove_order(int orderNumber);

    void modify_order(int orderNumber, const std::string& attribute, const std::string& value);

    bool search_order(int orderNumber) const;
};
