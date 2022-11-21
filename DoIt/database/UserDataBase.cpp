#include "UserDataBase.h"

#include <iostream>

UserDataBase::UserDataBase(std::shared_ptr<DataBase> cl) {
    client = cl;
}

json UserDataBase::addUser(const json &info) const {
    json response = client->insert(info);
    return response;
}

json UserDataBase::removeUser(const int id) const {
    json response = client->remove({{"id", id}});
    return response;
}

bool UserDataBase::checkUserExists(const int id) const {
    json response = client->select({{"id", id}});
    return true;
}

json UserDataBase::updateUser(const json &info) const {
    json response = client->update(info);
    return response;
}

json UserDataBase::getUserInfo(const int id) const {
    json response = client->select({{"id", id}});
    return response;
}

json UserDataBase::getUserBoards(const int id) const {
    json response = client->select({{"id", id}});
    return response;
}
