#include "UserDataBase.h"

#include <iostream>

UserDataBase::UserDataBase(std::shared_ptr<DataBase> cl) {
    client = cl;
}

json UserDataBase::addUser(const json &info) const {
    json response = client->insert(info);
    return response;
}

json UserDataBase::removeUser(const size_t id) const {
    json response = client->remove({{"id", id}});
    return response;
}

bool UserDataBase::checkUserExists(const size_t id) const {
    json response = client->select({{"id", id}});
    return true;
}

json UserDataBase::updateUser(const json &info) const {
    json response = client->update(info);
    return response;
}

json UserDataBase::getUserInfo(const size_t id) const {
    json response = client->select({{"id", id}});
    return response;
}

json UserDataBase::getUserBoards(const size_t id) const {
    json response = client->select({{"id", id}});
    return response;
}
