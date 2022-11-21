#include "BoardDataBase.h"

#include <iostream>

BoardDataBase::BoardDataBase(std::shared_ptr<DataBase> cl) {
    client = cl;
}

json BoardDataBase::addBoard(const json &info) const {
    json response = client->insert(info);
    return response;
}

json BoardDataBase::removeBoard(const int id) const {
    json response = client->remove({{"id", id}});
    return response;
}

json BoardDataBase::updateBoard(const json &info) const {
    json response = client->update(info);
    return response;
}

json BoardDataBase::getBoardInfo(const int id) const {
    json response = client->select({{"id", id}});
    return response;
}

json BoardDataBase::getBoardUsers(const int id) const {
    json response = client->select({{"id", id}});
    return response;
}

json BoardDataBase::getBoardColumns(const int id) const {
    json response = client->select({{"id", id}});
    return response;
}

json BoardDataBase::getBoardColumn(const int id, const int column_id) const {
    json response = client->select({{"id", id}});
    return response;
}

json BoardDataBase::addColumn(const json &info) const {
    json response = client->insert(info);
    return response;
}