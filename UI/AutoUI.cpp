//
// Created by ANDREI on 29/05/2024.
//

#include "AutoUI.h"
#include <iostream>

void AutoUI::printMenu() {
    std::cout << "Car Management System" << std::endl;
    std::cout << "1. Add car" << std::endl;
    std::cout << "2. Delete car" << std::endl;
    std::cout << "3. Modify car" << std::endl;
    std::cout << "4. List cars by price" << std::endl;
    std::cout << "5. Get car by license plate" << std::endl;
    std::cout << "6. Filter cars" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

void AutoUI::addAuto() {
    std::string licensePlate, model, brand, fuelType, transmission, color, remarks;
    bool isActive;
    int yearOfFirstRegistration;
    int mileage;
    float dailyRate;

    std::cout << "Enter license plate: ";
    std::cin >> licensePlate;
    std::cout << "Enter model: ";
    std::cin >> model;
    std::cout << "Enter brand: ";
    std::cin >> brand;
    std::cout << "Enter fuel type: ";
    std::cin >> fuelType;
    std::cout << "Enter transmission: ";
    std::cin >> transmission;
    std::cout << "Enter color: ";
    std::cin >> color;
    std::cout << "Enter remarks: ";
    std::cin >> remarks;
    std::cout << "Enter mileage: ";
    std::cin >> mileage;
    std::cout << "Enter daily Rate: ";
    std::cin >> dailyRate;
    std::cout << "Enter year of first registration: ";
    std::cin >> yearOfFirstRegistration;
    std::cout << "Enter activity status (true or false): ";
    std::cin >> isActive;

    try {
        Auto newAuto(licensePlate, model, brand, yearOfFirstRegistration,
                     mileage, dailyRate, fuelType, transmission, color, remarks);
        controller.addAuto(newAuto);
        std::cout << "New car added successfully!" << std::endl;
    }
    catch (std::invalid_argument e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


void AutoUI::removeAuto() {
    std::string licensePlate;
    std::cout << "Enter the license Plate: ";
    std::cin >> licensePlate;
    controller.removeAuto(licensePlate);
    std::cout << "Car removed successfully!";
}


void AutoUI::modifyAuto() {
    std::string licensePlate, model, brand, fuelType, transmission, color, remarks;
    bool isActive;
    int yearOfFirstRegistration;
    int mileage;
    float dailyRate;

    std::cout << "Enter licensePlate: ";
    std::cin >> licensePlate;
    std::cout << "Enter model: ";
    std::cin >> model;
    std::cout << "Enter brand: ";
    std::cin >> brand;
    std::cout << "Enter fuel type: ";
    std::cin >> fuelType;
    std::cout << "Enter transmission: ";
    std::cin >> transmission;
    std::cout << "Enter color: ";
    std::cin >> color;
    std::cout << "Enter remarks: ";
    std::cin >> remarks;
    std::cout << "Enter mileage: ";
    std::cin >> mileage;
    std::cout << "Enter daily rate: ";
    std::cin >> dailyRate;
    std::cout << "Enter year of first registration: ";
    std::cin >> yearOfFirstRegistration;
    std::cout << "Enter activity status (true or false): ";
    std::cin >> isActive;

    try {
        Auto newAuto(licensePlate, model, brand, yearOfFirstRegistration,
                     mileage, dailyRate, fuelType, transmission, color, remarks);
        controller.modifyAuto(newAuto);
        std::cout << "Car modified successfully!" << std::endl;
    }
    catch (std::invalid_argument e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


void AutoUI::listCarsByPrice() {
    controller.listCarsByPrice();
}


void AutoUI::getCarByLicensePlate() {
    std::string licensePlate;
    std::cout << "Enter a license plate: " << std::endl;
    std::cin >> licensePlate;
    controller.getCarByLicensePlate(licensePlate);
}


void AutoUI::filterByBrand() {
    std::string brand;
    std::cout << "Enter brand name: " << std::endl;
    std::cin >> brand;
    controller.filterByBrand(brand);
}


void AutoUI::filterByModel() {
    std::string model;
    std::cout << "Enter model name: " << std::endl;
    std::cin >> model;
    controller.filterByModel(model);
}


void AutoUI::filterByFuelType() {
    std::string fuelType;
    std::cout << "Enter fuel type: " << std::endl;
    std::cin >> fuelType;
    controller.filterByFuelType(fuelType);
}


void AutoUI::filterByTransmission() {
    std::string transmission;
    std::cout << "Enter transmission type: " << std::endl;
    std::cin >> transmission;
    controller.filterByTransmission(transmission);
}


void AutoUI::filterByPriceRange() {
    std::string priceRange;
    std::cout << "Enter price range: " << std::endl;
    std::cin >> priceRange;
    controller.filterByPriceRange(priceRange);
}


void AutoUI::run() {
    int choice;
    do {
        printMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                addAuto();
            case 2:
                removeAuto();
            case 3:
                modifyAuto();
            case 4:
                listCarsByPrice();
            case 5:
                getCarByLicensePlate();
            case 6:
                std::cout << "Choose filter: " << std::endl;
                std::cout << "1. Filter by brand" << std::endl;
                std::cout << "2. Filter by model" << std::endl;
                std::cout << "3. Filter by fuel type" << std::endl;
                std::cout << "4. Filter by transmission" << std::endl;
                std::cout << "5. Filter by price range" << std::endl;
                std::cin >> choice;
                switch (choice) {
                    case 1:
                        filterByBrand();
                    case 2:
                        filterByModel();
                    case 3:
                        filterByFuelType();
                    case 4:
                        filterByTransmission();
                    case 5:
                        filterByPriceRange();
                }
            case 0:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cerr << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0);
}