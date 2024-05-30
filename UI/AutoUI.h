//
// Created by ANDREI on 29/05/2024.
//

#ifndef JSON_TEST_CARUI_H
#define JSON_TEST_CARUI_H
#include "../Controllers/AutoController/AutoController.h"

class AutoUI {

private:
//    AutoUI& autoUI;
    AutoController& controller;
    void printMenu();
    void addAuto();
    void removeAuto();
    void modifyAuto();
    void filterByBrand();
    void filterByModel();
    void filterByFuelType();
    void filterByTransmission();
    void filterByPriceRange();
    void listCarsByPrice();
    void getCarByLicensePlate();

public:
    AutoUI(AutoController& controller);
    void run();

};

#endif //JSON_TEST_CARUI_H