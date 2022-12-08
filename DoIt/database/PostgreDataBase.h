#pragma once

#include <iostream>
#include <memory>
#include <pqxx/pqxx>
#include <string>

#include "database.h"

struct PostgreConnectParams {
    std::string dbName;
    std::string user;
    std::string password;
    std::string host;
    std::string port;

    PostgreConnectParams(std::string dbName, std::string user, std::string password = "postgres",
                         std::string host = "127.0.0.1", std::string port = "5432");

    std::string paramsToString() const;
};

class PostgreDataBase : public DataBase {
  public:
    PostgreDataBase() = default;
    PostgreDataBase(std::shared_ptr<PostgreConnectParams> conParams);

    json createTable(json) override;
    json dropTable(std::string) override;
    json update(json) override;
    json insert(json) override;
    json select(json) override;
    json remove(json) override;

  private:
    std::shared_ptr<PostgreConnectParams> connectParams;
    std::shared_ptr<pqxx::connection> con;
};
