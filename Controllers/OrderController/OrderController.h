#pragma once

#include "../../Domain/Order.h"
#include "../../Repositories/OrderRepo/OrderRepo.h"
#include <string>
#include <vector>
#include <stdexcept>

class OrderController {
public:
    OrderController(const std::string& filename);

    void createOrder(int ordNum, const std::string& ordDate, OrderStatus status, const std::string& car,
                     const std::string& start, const std::string& end, const std::string& cust,
                     const std::string& emp, double totalAmt, const std::string& rem, const std::string& userType);

    void modifyOrder(int ordNum, const std::string& attribute, const std::string& value, const std::string& emp, const std::string& userType);
    void removeOrder(int ordNum, const std::string& userType, const std::string& cust);
    std::vector<Order> listOrders(const std::string& startDate, const std::string& endDate);
    Order searchOrder(int ordNum);
    double calculateTotalSum(const std::string& period, const std::string& groupBy);

private:
    OrderRepo orderRepo;
    void validateOrder(const Order& order);
};