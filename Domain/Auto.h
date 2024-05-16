#ifndef CARSHARINGAPP_AUTO_H
#define CARSHARINGAPP_AUTO_H

#include <string>

struct FuelType{
    std::string benzin = "Benzin";
    std::string diesel = "Diesel";
    std::string electric = "Electric";
    std::string gas = "Gas";
};

struct TransmissionType{
    std::string automatik = "Automatik";
    std::string schaltgetriebe = "Schaltgetriebe"; //manual
};

class Auto {
private:
    std::string kennzeichen;
    std::string modell;
    std::string marke;
    int erstzulassungsjahr;
    int kilometerstand;
    double tagespreis;
    std::string kraftstoffart;
    std::string getriebe;
    std::string farbe;
    std::string bemerkung;

public:
    Auto(std::string kennz, std::string mod, std::string mark, int erstJahr,
         int kmStand, double tagPreis, std::string kraft, std::string getr,
         std::string farb, std::string bemerk);

    Auto(std::string kennz, std::string mod, std::string mark, int erstJahr,
         int kmStand, double tagPreis, std::string kraft, std::string getr,
         std::string farb);

    std::string getKennzeichen() const;

    std::string getModell() const;

    std::string getMarke() const;

    int getErstzulassungsjahr() const;

    int getKilometerstand() const;

    double getTagespreis() const;

    std::string getKraftstoffart() const;

    std::string getGetriebe() const;

    std::string getFarbe() const;

    std::string getBemerkung() const;
};
#endif //CARSHARINGAPP_AUTO_H