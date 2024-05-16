#ifndef JSON_TEST_AUTOCONTROLLER_H
#define JSON_TEST_AUTOCONTROLLER_H

#include <vector>
#include <string>
#include "../Domain/Auto.h" // Assuming this is the class for cars (Auto)
#include "../Repositories/AutoRepo/AutoRepo.h" // Repository for cars

class AutoController {
public:
    // Constructor
    AutoController(AutoRepo& repo);

    std::vector<Auto> convertAllCars();

    // Filter cars by a given brand
    std::vector<Auto> filterByBrand(const std::string& brand);

    // Filter cars by a given model
    std::vector<Auto> filterByModel(const std::string& model);

    // Filter cars by a given fuel type
    std::vector<Auto> filterByFuelType(const std::string& fuelType);

    // Filter cars by a given transmission type
    std::vector<Auto> filterByTransmission(const std::string& transmission);

    // Filter cars by price range
    std::vector<Auto> filterByPriceRange(double minPrice, double maxPrice);

    // List all cars sorted by daily price in ascending order
    std::vector<Auto> listCarsByPrice();

    // Get a car by its license plate
    Auto getCarByLicensePlate(const std::string& licensePlate);

    void addAuto(std::string kennzeichen, std::string modell, std::string marke, int erstzulassungsjahr, int kilometerstand, double tagespreis, std::string kraftstoffart, std::string getriebe, std::string farbe, std::string bemerkung);

    void removeAuto(const std::string& licensePlate);

    void modifyAuto(const std::string& licensePlate, const std::string& attribute, const std::string& value);

private:
    AutoRepo& repo; // Reference to the repository
};
#endif
