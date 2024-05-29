#ifndef ADMINREPO_H
#define ADMINREPO_H
#pragma once

#include "../include/nlohmann/json.hpp"
#include <string>
#include "../Domain/Admin.h"



using json = nlohmann::json;


class AdminRepo {
private:
    json admins;
    std::string filename;
    void read_from_file(const std::string& filename);

    void write_to_file(std::string& filename);

    bool verify_admin(Admin& admin) const;

    void save();

    using json = nlohmann::json;

    public:

    AdminRepo(const std::string& filename);
    json& get_admin_json();
    void add_admin(Admin& admin);
    void remove_admin(const std::string& identifier);
    bool search_admin(const std::string email) const;
    void modify_admin(std::string identifier, std::string attribute, std::string value);


};
#endif//