#pragma once

#include <string>

#include "PostgreDataBase.h"
#include "database.h"

class UserDataBase {
 public:
    UserDataBase() = default;
    UserDataBase(std::shared_ptr<DataBase> client);
    json addUser(const json &info) const;
    json removeUser(const int id) const;
    bool checkUserExists(const int id) const;
    json updateUser(const json &info) const;
    json getUserInfo(const int id) const;
    json getUserBoards(const int id) const;

 private:
    std::shared_ptr<DataBase> client;
};