#include "PostgreDataBase.h"

#include <iostream>

PostgreConnectParams::PostgreConnectParams(std::string dbName, std::string user, std::string password,
                                           std::string host, std::string port)
    : dbName(dbName), user(user), password(password), host(host), port(port) {}

std::string PostgreConnectParams::paramsToString() const {
    std::string strParams = "dbname = " + dbName + " ";
    strParams += "user = " + user + " ";

    if (!password.empty()) {
        strParams += "password = " + password + " ";
    }

    if (!host.empty()) {
        strParams += "host = " + host + " ";
    }

    if (!port.empty()) {
        strParams += "port = " + port + " ";
    }

    std::cout << strParams;
    return strParams;
}

PostgreDataBase::PostgreDataBase(std::shared_ptr<PostgreConnectParams> conParams) : connectParams(conParams) {
    con = std::make_shared<pqxx::connection>(connectParams->paramsToString());

    if ((*con).is_open()) {
        std::cout << "Opened database successfully: " << (*con).dbname() << std::endl;
    } else {
        std::cout << "Can't open database" << std::endl;
    }
}

json PostgreDataBase::createTable(json request) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    return response;
}

json PostgreDataBase::dropTable(std::string) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    return response;
}

json PostgreDataBase::select(json request) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    return response;
}

json PostgreDataBase::insert(json request) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    return response;
}

json PostgreDataBase::remove(json request) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    return response;
}

json PostgreDataBase::update(json request) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    return response;
}