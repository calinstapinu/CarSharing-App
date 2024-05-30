//
// Created by ANDREI on 29/05/2024.
//

#ifndef JSON_TEST_FINALUI_H
#define JSON_TEST_FINALUI_H

//#include "../Controllers/AdminController/AdminController.h"
#include "AutoUI.h"
#include "EmployeeUI.h"
#include "CustomerUI.h"
#include "OrderUI.h"

class FinalUI {

private:
    void startMenu();
    void displayMenuEmployee();
    void handleMenuEmployee();
    void logIn();
    void signUp();

public:
    void runAll();

};


#endif //JSON_TEST_FINALUI_H