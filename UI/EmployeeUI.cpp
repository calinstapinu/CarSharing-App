#include "EmployeeUI.h"

EmployeeUI::EmployeeUI(EmployeeUI& employeeUI) : UI(UI) {}

void EmployeeUI::displayMenu() {
    std::cout << "Employee Management System" << std::endl;
    std::cout << "1. Add Employee" << std::endl;
    std::cout << "2. Remove Employee" << std::endl;
    std::cout << "3. Modify Employee" << std::endl;
    std::cout << "4. Search Employee" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

void EmployeeUI::handleMenu() {
    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                removeEmployee();
                break;
            case 3:
                modifyEmployee();
                break;
            case 4:
                searchEmployee();
                break;

            case 0:
                std::cout << "Exiting" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0);
}

void EmployeeUI::addEmployee() {
    std::string name, surname, email, password, position, birthdate, abbreviation, remarks;
    float salary;

    std::cout << "Enter last name: ";
    std::getline(std::cin, lastName);
    std::cout << "Enter fisrt name: ";
    std::getline(std::cin, firstName);
    std::cout << "Enter email: ";
    std::getline(std::cin, email);
    // std::cout << "Enter password: ";
    // std::getline(std::cin, password);
    std::cout << "Enter position: ";
    std::getline(std::cin, position);
    // std::cout << "Enter birthdate: ";
    // std::getline(std::cin, birthdate);
    std::cout << "Enter abreviation: ";
    std::getline(std::cin, abbreviation);
    std::cout << "Enter birth date: ";
    std::getline(std::cin, birthDateString);
    std::cout << "Enter salary: ";
    std::cin >> salary;
    std::cin.ignore();
    std::cout << "Enter remarks: ";
    std::getline(std::cin, remarks);
    std::cout << "admin: ";
    std::getline(std::cin, isAdmin);

    controller.addEmployee(lastName, firstName, email, position, abbreviation, birthDateString, salary, remarks, isAdmin);
}
void EmployeeUI::removeEmployee() {
    std::string name, surname;
    std::cout << "Enter last name: ";
    std::getline(std::cin, lastName);
    std::cout << "Enter first name: ";
    std::getline(std::cin, firstName);

    controller.removeEmployee(lastName, fisrtName);
}

void EmployeeUI::modifyEmployee() {
    std::string name, surname, email, password, position, birthdate, abbreviation, remarks;
    float Salary;

    std::cout << "Enter last name: ";
    std::getline(std::cin, lastName);
    std::cout << "Enter fisrt name: ";
    std::getline(std::cin, firstName);
    std::cout << "Enter email: ";
    std::getline(std::cin, email);
    std::cout << "Enter position: ";
    std::getline(std::cin, position);
    std::cout << "Enter abreviation: ";
    std::getline(std::cin, abbreviation);
    std::cout << "Enter birth date: ";
    std::getline(std::cin, birthDateString);
    std::cout << "Enter salary: ";
    std::cin >> salary;
    std::cin.ignore();
    std::cout << "Enter remarks: ";
    std::getline(std::cin, remarks);
    std::cout << "admin: ";
    std::getline(std::cin, isAdmin);

    controller.modifyEmployee(lastName, firstName, email, position, abbreviation, birthDateString, salary, remarks, isAdmin);
}


//verifica cu controllerul
void EmployeeUI::searchEmployee() {
    std::string identifier;
    std::cout << "Enter the employee identifier to search: ";
    std::cin >> identifier;
    if (employeeController.searchEmployee(identifier)) {
        std::cout << "Employee found." << std::endl;
        json employeeJson = employeeRepo.get_mitarbeiter_json();
        std::cout << employeeJson.dump(4) << std::endl;
    } else {
        std::cout << "Employee not found." << std::endl;
    }
}