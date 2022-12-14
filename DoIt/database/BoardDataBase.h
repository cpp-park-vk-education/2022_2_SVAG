#pragma once

#include <string>

#include "PostgreDataBase.h"
#include "database.h"

class BoardDataBase {
 public:
    BoardDataBase() = default;
    BoardDataBase(std::shared_ptr<DataBase> client);
    json addBoard(const json &info) const;
    json removeBoard(const size_t id) const;
    json updateBoard(const json &info) const;
    json getBoardInfo(const size_t id) const;
    json getBoardUsers(const size_t id) const;
    json getBoardColumns(const size_t id) const;
    json getBoardColumn(const size_t id, const size_t column_id) const;
    json addColumn(const json &info) const;

 private:
    std::shared_ptr<DataBase> client;
};
