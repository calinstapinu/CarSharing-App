#include "Auto.h"
#include <string>

// Constructor
Auto::Auto(std::string kennz, std::string mod, std::string mark, int erstJahr,
           int kmStand, double tagPreis, std::string kraft, std::string getr,
           std::string farb, std::string bemerk) :
        kennzeichen(kennz), modell(mod), marke(mark), erstzulassungsjahr(erstJahr),
        kilometerstand(kmStand), tagespreis(tagPreis), kraftstoffart(kraft),
        getriebe(getr), farbe(farb), bemerkung(bemerk) {}

Auto::Auto(std::string kennz, std::string mod, std::string mark, int erstJahr, int kmStand, double tagPreis,
           std::string kraft, std::string getr, std::string farb):
           kennzeichen(kennz), modell(mod), marke(mark), erstzulassungsjahr(erstJahr),
           kilometerstand(kmStand), tagespreis(tagPreis), kraftstoffart(kraft),
           getriebe(getr), farbe(farb), bemerkung("") {}

std::string Auto::getKennzeichen() const {
    return kennzeichen;
}

std::string Auto::getModell() const {
    return modell;
}

std::string Auto::getMarke() const {
    return marke;
}

int Auto::getErstzulassungsjahr() const {
    return erstzulassungsjahr;
}

int Auto::getKilometerstand() const {
    return kilometerstand;
}

double Auto::getTagespreis() const {
    return tagespreis;
}

std::string Auto::getKraftstoffart() const {
    return kraftstoffart;
}

std::string Auto::getGetriebe() const {
    return getriebe;
}

std::string Auto::getFarbe() const {
    return farbe;
}

std::string Auto::getBemerkung() const {
    return bemerkung;
}
