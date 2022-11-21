#pragma once

#include <string>

#include "PostgreDataBase.h"
#include "database.h"

class BoardDataBase {
 public:
    BoardDataBase() = default;
    BoardDataBase(std::shared_ptr<DataBase> client);
    json addBoard(const json &info) const;
    json removeBoard(const int id) const;
    json updateBoard(const json &info) const;
    json getBoardInfo(const int id) const;
    json getBoardUsers(const int id) const;
    json getBoardColumns(const int id) const;
    json getBoardColumn(const int id, const int column_id) const;
    json addColumn(const json &info) const;

 private:
    std::shared_ptr<DataBase> client;
};
