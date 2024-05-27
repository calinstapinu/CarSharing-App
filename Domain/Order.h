#ifndef CARSHARINGAPP_ORDER_H
#define CARSHARINGAPP_ORDER_H

#include <string>

enum class OrderStatus { Reservation, Order, Completed };

class Order {
private:
    int orderNumber;
    std::string orderDate;
    OrderStatus status;
    std::string car;
    std::string start;
    std::string end;
    std::string customer;
    std::string employee;
    double totalAmount;
    std::string remark;

public:
    Order(int ordNum, std::string ordDate, OrderStatus stat, std::string car,
          std::string start, std::string end, std::string cust, std::string emp,
          double totalAmt, std::string rem);

    // Getters
    int getOrderNumber() const;
    std::string getOrderDate() const;
    OrderStatus getStatus() const;
    std::string getCar() const;
    std::string getStart() const;
    std::string getEnd() const;
    std::string getCustomer() const;
    std::string getEmployee() const;
    double getTotalAmount() const;
    std::string getRemark() const;

    // Setters
    void setOrderDate(const std::string& ordDate);
    void setStatus(OrderStatus stat);
    void setCar(const std::string& car);
    void setStart(const std::string& start);
    void setEnd(const std::string& end);
    void setCustomer(const std::string& cust);
    void setEmployee(const std::string& emp);
    void setTotalAmount(double totalAmt);
    void setRemark(const std::string& rem);
};

#endif //CARSHARINGAPP_ORDER_H
