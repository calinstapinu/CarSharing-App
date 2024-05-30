//
// Created by Kathrin Bercea Engels on 29.05.2024.
//

#ifndef JSON_TEST_EMPLOYEEUI_H
#define JSON_TEST_EMPLOYEEUI_H
#include <iostream>
#include <string>

class EmployeeUI {

public:
    EmployeeUI(EmployeeUI& employeeUI);

    void displayMenu();
    void handleMenu();


private:
    EmployeeUI& employeeUi;

    void addEmployee();
    void removeEmployee();
    void modifyEmployee();
    void searchEmployee();

};


#endif //JSON_TEST_EMPLOYEEUI_H