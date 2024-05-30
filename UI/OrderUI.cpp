//
// Created by Kathrin Bercea Engels on 29.05.2024.
//

#include "OrderUI.h"
#include "../Domain/Order.h"
#include <iomanip>
#include <string>

void OrderUI::displayMenu() {
    std::cout << "Order Management System\n";
    std::cout << "1. Create Order\n";
    std::cout << "2. Modify Order\n";
    std::cout << "3. Remove Order\n";
    std::cout << "4. List Orders\n";
    std::cout << "5. Search Order\n";
    std::cout << "6. Calculate Total Sum\n";
    std::cout << "0. Exit\n";
}

void OrderUI::handleUserInput(int userType) {
    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                createOrder();
                break;
            case 2:
                modifyOrder(userType);
                break;
            case 3:
                removeOrder();
                break;
            case 4:
                listOrders();
                break;
            case 5:
                searchOrder();
                break;
            case 6:
                calculateTotalSum();
                break;
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);
}

void OrderUI::createOrder() {
    int ordNum;
    std::string ordDate, car, start, end, cust, emp, rem, statusStr;
    double totalAmt;
    OrderStatus status;
    std::string userType;

    std::cout << "Enter Order Number: ";
    std::cin >> ordNum;

    std::cout << "Enter Order Date (YYYY-MM-DD): ";
    std::cin >> ordDate;

    std::cout << "Enter Order Status (Reservation/Order/Completed): ";
    std::cin >> statusStr;
    status = stringToOrderStatus(statusStr);

    std::cout << "Enter Car: ";
    std::cin >> car;

    std::cout << "Enter Start Date (YYYY-MM-DD): ";
    std::cin >> start;

    std::cout << "Enter End Date (YYYY-MM-DD): ";
    std::cin >> end;

    std::cout << "Enter Customer: ";
    std::cin >> cust;

    std::cout << "Enter Employee: ";
    std::cin >> emp;

    std::cout << "Enter Total Amount: ";
    std::cin >> totalAmt;

    std::cout << "Enter Remark: ";
    std::cin.ignore();

    std::getline(std::cin, rem);
    std::cout << "Enter User Type (employee/admin): ";

    std::cin >> userType;
}

void OrderUI::modifyOrder(int userType) {
    int ordNum;
    std::string attribute, value, emp, userTypeStr;

    std::cout << "Enter Order Number: ";
    std::cin >> ordNum;

    std::cout << "Enter Attribute to Modify (orderDate, status, car, start, end, customer, employee, totalAmount, remark): ";
    std::cin >> attribute;

    std::cout << "Enter New Value for " << attribute << ": ";
    std::cin.ignore();
    std::getline(std::cin, value);

    std::cout << "Enter Employee ID: ";
    std::getline(std::cin, emp);

    if (userType == 1) {
        userTypeStr = "employee";
    } else if (userType == 2) {
        userTypeStr = "admin";
    } else {
        std::cout << "Invalid user type. Modification aborted." << std::endl;
        return;
    }

    try {
        OrderController.modifyOrder(ordNum, attribute, value, emp, userTypeStr);
        std::cout << "Order modified successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void  OrderUI::removeOrder() {
    int id;
    std::cout << " Enter order ID to remove: ";
    std::cin >> id;
    OrderController.removeOrder(id);


    void OrderUI::listOrders() {
        auto orders = controller.listOrders();
        for (Order order: orders) {
            order.displayOrder();
        }
    }

    void OrderUI::searchOrder() {
        int id;
        std::cout << " Enter order ID to search: ";
        std::cin >> id;
        auto order = controller.searchOrder(id);
        order.displayOrder();
    }

}