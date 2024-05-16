#include <iostream>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"
#include "AutoRepo.h"
#include <typeinfo>
#include <cctype>

using namespace std;

/// FUNCTII AJUTATOARE
// convert Kennzeichen la majuscule
std::string convertToUpperCase(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (std::isdigit(c)) {
            result += c;
        } else {
            result += std::toupper(c);
        }
    }
    return result;
}

std::string convertToLowerCase(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (std::isdigit(c)) {
            result += c;
        } else {
            result += std::tolower(c);
        }
    }
    return result;
}

bool verifyVIN(const std::string& kennzeichen){
    for (char c: kennzeichen)
        if (!std::isdigit(c) && !std::isalpha(c))
            return false;
    return true;
}

/// IMPLEMENTARE REPO
// La startul programului, array-ul cars primeste toate obiectele json din fisier
AutoRepo::AutoRepo(const std::string& filename) {
    this->filename = filename;
    this->read_from_file(this->filename);
}

void AutoRepo::add_car(Auto car) {
    this->verify_car(car);

    json j;
    j["kennzeichen"] = convertToUpperCase(car.getKennzeichen());
    j["modell"] = car.getModell();
    j["marke"] = car.getMarke();
    j["erstzulassungsjahr"] = car.getErstzulassungsjahr();
    j["kilometerstand"] = car.getKilometerstand();
    j["tagespreis"] = car.getTagespreis();
    j["kraftstoffart"] = car.getKraftstoffart();
    j["getriebe"] = car.getGetriebe();
    j["farbe"] = car.getFarbe();
    j["bemerkung"] = (car.getBemerkung() != "") ? car.getBemerkung() : "";
    j["aktiv"] = "ja";
    j["bestellt"] = "nein";

    this->cars.push_back(j);
    this->write_to_file(this->filename);

}

void AutoRepo::remove_car(const std::string& identifier) {
    string converted_identifier = convertToUpperCase(identifier);
    auto it = std::remove_if(this->cars.begin(), this->cars.end(),
                             [&converted_identifier](const json& carJson) {
                                 return carJson["kennzeichen"] == converted_identifier && carJson["bestellt"] != "ja";
                             });

    if (it != this->cars.end() && (*it)["bestellt"] != "ja") {
        this->cars.erase(it, this->cars.end());
        this->write_to_file(this->filename);
        return;
    }
    throw runtime_error("Auto mit Kennzeichen: " + converted_identifier + " existiert nicht oder hat eine aktive Bestellung.");
}

/// PRIVATE METHODEN
void AutoRepo::write_to_file(std::string filename) {
        std::ofstream file(filename);
        if(file.is_open()) {
            file << this->cars.dump(4); // array-ul intreg este scris in fisier
            file.close();                      // cu indent 4
            return;
        }
        throw runtime_error("Error opening " + filename);
}

void AutoRepo::read_from_file(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return;
    }

    json j;
    file >> j; // se citeste tot array-ul din fisier

    if (j.is_array())
        for (const auto& carJson : j)
            this->cars.push_back(carJson); // fiecare obiect json din array este
    file.close();                              // introdus in array
}

bool AutoRepo::search_car(const std::string& kennzeichen) const {
    for (const auto& obj : this->cars) {
        if (obj["kennzeichen"] == kennzeichen)
            return true;
    }
    return false;
}

/// VERIFICARE INAINTE DE ADD
bool AutoRepo::verify_car(const Auto car) const{
    if (car.getKennzeichen().empty() || !verifyVIN(car.getKennzeichen()))
        throw runtime_error("Invalid Kennzeichen.");
    if (search_car(convertToUpperCase(car.getKennzeichen())))
        throw runtime_error("Auto mit Kennzeichen: " + convertToUpperCase(car.getKennzeichen()) + " existiert schon.");
    if (car.getTagespreis() < 0)
        throw runtime_error("Tagespreis kann nicht kleiner als Null sein.");
    if (car.getErstzulassungsjahr() > 2024 || car.getErstzulassungsjahr() < 2000)
        throw runtime_error("Ersatzlassungsjahr soll zwischen 2000 und 2024 sein.");
    if (car.getKilometerstand() < 0)
        throw runtime_error("Kilometerstand darf nicht negativ sein");
    if (car.getKraftstoffart() != "Diesel" && car.getKraftstoffart() != "Benzin" &&
            car.getKraftstoffart() != "Electric" && car.getKraftstoffart() != "Gas")
        throw runtime_error("Invalid Kraftstoffart: Diesel/Benzin/Electric/Gas");
    if (car.getGetriebe() != "Automatik" && car.getGetriebe() != "Schaltgetriebe")
        throw runtime_error("Invalid Getriebe: Automatik/Schaltgetriebe");
    return true;
}

json& AutoRepo::get_cars_json() {
    return this->cars;
}

void AutoRepo::modify_car(const std::string& kennzeichen, const std::string& attribute, const std::string& value) {
    string kennezeichen_gross = convertToUpperCase(kennzeichen);
    string convertedAttribute = convertToLowerCase(attribute);
    if (convertedAttribute != "kennzeichen" && convertedAttribute != "modell" && convertedAttribute != "marke" && convertedAttribute != "tagespreis" &&
            convertedAttribute != "erstzulassungsjahr" && convertedAttribute != "kilometerstand" && convertedAttribute != "kraftstoffart" &&
            convertedAttribute != "getriebe" && convertedAttribute != "farbe" && convertedAttribute != "bemerkung" &&
            convertedAttribute != "aktiv" && convertedAttribute != "bestellt")
        throw runtime_error("Invalid attribute.");

    if (!this->search_car(kennezeichen_gross))
        throw runtime_error("Auto mit Kennzeichen: " + kennezeichen_gross + " existiert nicht.");


    for (auto& obj : this->cars) {
        if (obj["kennzeichen"] == kennezeichen_gross) {
            if (convertedAttribute == "erstzulassungsjahr" || convertedAttribute == "kilometerstand") {
                if (convertedAttribute == "erstzulassungsjahr" && stoi(value) >= 2000 && stoi(value) <= 2024)
                    obj[convertedAttribute] = stoi(value);
                else if(convertedAttribute == "kilometerstand" && stoi(value) >= 0)
                    obj[convertedAttribute] = stoi(value);
                else
                    throw runtime_error("Invalide Veranderungen.");
            }
            else if (convertedAttribute == "tagespreis") {
                if (stod(value) >= 0)
                    obj[convertedAttribute] = stod(value);
                else
                    throw runtime_error("Invalide Veranderungen.");
            }
            else if (convertedAttribute == "kraftstoffart" && value != "Diesel" && value != "Benzin" && value != "Electric" && value != "Gas")
                throw runtime_error("Invalide Kraftstoffart: Diesel/Benzin/Electric/Gas");
            else if (convertedAttribute == "getriebe" && value != "Automatik" && value != "Schaltgetriebe")
                throw runtime_error("Invalide Getriebe: Automatik/Schaltgetriebe");
            else if (convertedAttribute == "aktiv" && value != "ja" && value != "nein")
                throw runtime_error("Invalid Aktiv Status: ja/nein");
            else if (convertedAttribute == "bestellt" && value != "ja" && value != "nein")
                throw runtime_error("Invalid Bestellt Status: ja/nein");
            else {
                if (convertedAttribute == "aktiv" && obj["aktiv"] == "ja" && obj["bestellt"] == "ja" && value == "nein")
                    throw runtime_error("Verboten. Man darf nicht das Auto " + kennezeichen_gross + " deaktivieren, weil es eine aktive Bestellung hat.");
                obj[convertedAttribute] = value;
            }
            break;
        }
    }
    this->write_to_file(this->filename);
}

void AutoRepo::save() {
    this->write_to_file(this->filename);
}

/// Metode suplimentare
//void AutoRepo::print_cars() {
//    for (const auto& obj : this->cars) {
//        cout << obj["kennzeichen"] << " " << " " << obj["modell"] << " " << obj["marke"] << " " << obj["erstzulassungsjahr"]
//             << " " << obj["kilometerstand"] << " " << obj["tagespreis"] << " " << obj["kraftstoffart"] << " "
//             << obj["getriebe"] << " " << obj["farbe"] << " " << obj["bemerkung"]  << "\n";
//    }
//}
//
//
//list<Auto>&AutoRepo::get_cars() {
//    for (auto& obj : this->cars){
//        string kennzeichen = obj["kennzeichen"];
//        string modell = obj["modell"];
//        string marke = obj["marke"];
//        int erstzulassungsjahr = int(obj["erstzulassungsjahr"]);
//        int kilometerstand = int(obj["kilometerstand"]);
//        double tagespreis = double(obj["tagespreis"]);
//        string kraftstoffart = obj["kraftstoffart"];
//        string getriebe = obj["getriebe"];
//        string farbe = obj["farbe"];
//        string bemerkung;
//        if (!obj["bemerkung"].empty()){
//            bemerkung = obj["bemerkung"];
//            this->cars_obj.push_back(Auto(kennzeichen, modell, marke, erstzulassungsjahr, kilometerstand,
//                                          tagespreis, kraftstoffart, getriebe, farbe, bemerkung));
//        }
//        else
//            this->cars_obj.push_back(Auto(kennzeichen, modell, marke, erstzulassungsjahr, kilometerstand,
//                                          tagespreis, kraftstoffart, getriebe, farbe));
//    }
//    return this->cars_obj;
//}