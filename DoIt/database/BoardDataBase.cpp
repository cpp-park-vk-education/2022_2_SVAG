#include "BoardDataBase.h"

#include <iostream>

BoardDataBase::BoardDataBase(std::shared_ptr<DataBase> cl) {
    client = cl;
}

json BoardDataBase::addBoard(const json &info) const {
    json response = client->insert(info);
    return response;
}

json BoardDataBase::removeBoard(const size_t id) const {
    json response = client->remove({{"id", id}});
    return response;
}

json BoardDataBase::updateBoard(const json &info) const {
    json response = client->update(info);
    return response;
}

json BoardDataBase::getBoardInfo(const size_t id) const {
    json response = client->select({{"id", id}});
    return response;
}

json BoardDataBase::getBoardUsers(const size_t id) const {
    json response = client->select({{"id", id}});
    return response;
}

json BoardDataBase::getBoardColumns(const size_t id) const {
    json response = client->select({{"id", id}});
    return response;
}

json BoardDataBase::getBoardColumn(const size_t id, const size_t column_id) const {
    json response = client->select({{"id", id}});
    return response;
}

json BoardDataBase::addColumn(const json &info) const {
    json response = client->insert(info);
    return response;
}