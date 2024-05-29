#include "Order.h"

// Constructor
Order::Order(int ordNum, std::string ordDate, OrderStatus stat, std::string car,
             std::string start, std::string end, std::string cust, std::string emp,
             double totalAmt, std::string rem) :
        orderNumber(ordNum), orderDate(ordDate), status(stat), car(car),
        start(start), end(end), customer(cust), employee(emp),
        totalAmount(totalAmt), remark(rem) {}

// Getters
int Order::getOrderNumber() const {
    return orderNumber;
}

std::string Order::getOrderDate() const {
    return orderDate;
}

OrderStatus Order::getStatus() const {
    return status;
}

std::string Order::getCar() const {
    return car;
}

std::string Order::getStart() const {
    return start;
}

std::string Order::getEnd() const {
    return end;
}

std::string Order::getCustomer() const {
    return customer;
}

std::string Order::getEmployee() const {
    return employee;
}

double Order::getTotalAmount() const {
    return totalAmount;
}

std::string Order::getRemark() const {
    return remark;
}

// Setters
void Order::setOrderDate(const std::string& ordDate) {
    orderDate = ordDate;
}

void Order::setStatus(OrderStatus stat) {
    status = stat;
}

void Order::setCar(const std::string& car) {
    this->car = car;
}

void Order::setStart(const std::string& start) {
    this->start = start;
}

void Order::setEnd(const std::string& end) {
    this->end = end;
}

void Order::setCustomer(const std::string& cust) {
    customer = cust;
}

void Order::setEmployee(const std::string& emp) {
    employee = emp;
}

void Order::setTotalAmount(double totalAmt) {
    totalAmount = totalAmt;
}

void Order::setRemark(const std::string& rem) {
    remark = rem;
}
