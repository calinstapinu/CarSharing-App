#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "../include/nlohmann/json.hpp"
//#include "nlohmann/json.hpp"
#include "../../Domain/Auto.h"

using json = nlohmann::json;

class AutoRepo{
private:
    json cars;
    std::string filename;

    void read_from_file(const std::string& filename);

    void write_to_file(std::string filename);

    bool verify_car(const Auto car) const; // verifica toate aspectele masinii inainte de add

    void save();

public:
    AutoRepo(const std::string& filename); /// Constructor => filename pentru proiect este "cars.json"

    /// Trimite array-ul cu obiecte de tip JSON
    /// se pot accesa elementele intr-un for: de ex. auto["marke"]
    /// trebuie neaparat ghilimele si sa corespunda campurilor din AutoRepo.cpp - functia de add
    // TODO Important: dupa fiecare modificare (add, remove, modify), reapeleaza functia get_cars_json
    // TODO Exemplu: json cars = autoRepo.get_cars_json() ... (adaugi o masina) => cars = autoRepo.get_cars_json()
    // TODO Info: in felul asta, ramane actualizat array-ul in Controller
    json& get_cars_json();

    /// Adauga un obiect de tip Auto la array-ul de obiecte JSON
    /// Toate proprietatile masinii sunt verificate inainte de a adauga masina
    /// In cazul in care ceva nu corespunda => se arunca exceptii => trebuie cu TRY si CATCH
    /// folosite in Controller / UI
    void add_car(Auto car);

    /// Sterge masina din array-ul de masini
    /// Trebuie trimis ca parametru un string, care sa corespunda unui Kennzeichen existent
    /// stringul poate fi scris si cu litere mici, pentru ca este convertit automat la formatul bun
    /// In cazul in care nu exista nicio masina cu acel Kennzeichen => se arunca exceptie
    /// In cazul in care masina cu acel Kennzeichen are un Bestellung activ => se arunca exceptie
    /// Daca masina a fost stearsa, nu se arunca nicio exceptie
    void remove_car(const std::string& identifier);

    /// Modifica un atribut al unei masini
    /// Parametrii: 1. kennzeichen (unic pt fiecare masina)
    // 2. attribute trebuie sa fie un string cu unul dintre parametrii:
    // kennzeichen, modell, marke, erstzulassungsjahr, kilometerstand, tagespreis, kraftstoffart
    // getriebe, farbe, bemerkung, aktiv, bestellung - DOAR ASTEA SUNT VALIDE (pot fi scrise in orice
    // fel, deoarece sunt convertite la formatul corect in functie)
    /// 3. value => trebuie sa fie o valoare valida pentru atributul modificat
    void modify_car(const std::string& kennzeichen, const std::string& attribute, const std::string& value);

    /// Returneaz true daca exista o masina cu acel kennzeichen, false altfel
    bool search_car(const std::string& kennzeichen) const;
};