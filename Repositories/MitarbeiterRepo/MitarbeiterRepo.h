#pragma once

#ifndef JSON_TEST_MITARBEITERREPO_H
#define JSON_TEST_MITARBEITERREPO_H

#include "nlohmann/json.hpp"
#include "../../Domain/Mitarbeiter.h"


using json = nlohmann::json;


class MitarbeiterRepo {
private:
    json mitarbeiter;  ///< JSON array containing the employee data
    std::string filename; ///< Filename for storing the employee data

public:
    explicit MitarbeiterRepo(const std::string& filename);

    void write_to_file(const std::string &filename);
    void read_from_file(const std::string &filename);
    bool verify_employee(const Mitarbeiter& employee) const;
    void save();
    const json& get_mitarbeiter_json() const;
    void remove_employee(const std::string& identifier);
    void add_employee(const Mitarbeiter& employee);
    void modify_employee(const std::string& identifier, const std::string& attribute, const std::string& value);
    bool search_employee(const std::string& identifier) const;

};

#endif //JSON_TEST_MITARBEITERREPO_H