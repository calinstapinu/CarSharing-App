#include "AutoController.h"
#include <algorithm>

Auto from_json(const nlohmann::json& j) {
    return Auto(j["kennzeichen"], j["modell"], j["marke"], j["erstzulassungsjahr"], j["kilometerstand"], j["tagespreis"], j["kraftstoffart"], j["getriebe"], j["farbe"], j["bemerkung"]);
}

std::vector<Auto>AutoController :: convertAllCars() {
    std::vector<Auto> result;
    for (const auto& car : repo.get_cars_json()) {
        Auto newCar = from_json(car);
        result.push_back(newCar);
    }
    return result;
}

// Constructor
AutoController::AutoController(AutoRepo& repo) : repo(repo) {}

// Filter cars by brand
std::vector<Auto> AutoController::filterByBrand(const std::string& brand) {
    std::vector<Auto> result;
    for (const auto& car : repo.get_cars_json()) {
        if (car["marke"] == brand) {
            Auto newCar = from_json(car);
            result.push_back(newCar);
        }
    }
    return result;
}

// Filter cars by model
std::vector<Auto> AutoController::filterByModel(const std::string& model) {
    std::vector<Auto> result;
    for (const auto& car : repo.get_cars_json()) {
        if (car["modell"] == model) {
            Auto newCar = from_json(car);
            result.push_back(newCar);
        }
    }
    return result;
}

// Filter cars by fuel type
std::vector<Auto> AutoController::filterByFuelType(const std::string& fuelType) {
    std::vector<Auto> result;
    for (const auto& car : repo.get_cars_json()) {
        if (car["kraftstoffart"] == fuelType) {
            Auto newCar = from_json(car);
            result.push_back(newCar);
        }
    }
    return result;
}

// Filter cars by transmission type
std::vector<Auto> AutoController::filterByTransmission(const std::string& transmission) {
    std::vector<Auto> result;
    for (const auto& car : repo.get_cars_json()) {
        if (car["getriebe"] == transmission) {
            Auto newCar = from_json(car);
            result.push_back(newCar);
        }
    }
    return result;
}

// Filter cars by price range
std::vector<Auto> AutoController::filterByPriceRange(double minPrice, double maxPrice) {
    std::vector<Auto> result;
    for (const auto& car : repo.get_cars_json()) {
        if (car["tagespreis"] >= minPrice && car["tagespreis"] <= maxPrice) {
            Auto newCar = from_json(car);
            result.push_back(newCar);
        }
    }
    return result;
}

// List all cars sorted by daily price in ascending order
std::vector<Auto> AutoController::listCarsByPrice() {
    std::vector<Auto> result = convertAllCars();
    std::sort(result.begin(), result.end(), [](const Auto& a, const Auto& b) {
        return a.getTagespreis() < b.getTagespreis();
    });
    return result;
}

// Get a car by its license plate
Auto AutoController::getCarByLicensePlate(const std::string& licensePlate) {
    for (const auto& car : repo.get_cars_json()) {
        if (car["kennzeichen"]== licensePlate) {
            return from_json(car);
        }
    }
    throw std::runtime_error("Car not found");
}

void AutoController::addAuto(std::string kennzeichen, std::string modell, std::string marke, int erstzulassungsjahr, int kilometerstand, double tagespreis, std::string kraftstoffart, std::string getriebe, std::string farbe, std::string bemerkung) {
    Auto newCar(kennzeichen, modell, marke, erstzulassungsjahr, kilometerstand, tagespreis, kraftstoffart, getriebe, farbe, bemerkung);
    repo.add_car(newCar);
}

void AutoController::removeAuto(const std::string& licensePlate) {
    repo.remove_car(licensePlate);
}

void AutoController::modifyAuto(const std::string& licensePlate, const std::string& attribute, const std::string& value) {
    repo.modify_car(licensePlate, attribute, value);
}