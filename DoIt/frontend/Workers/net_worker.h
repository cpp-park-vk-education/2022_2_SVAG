#pragma once

#include <iostream>
#include <fstream>

#include <boost/asio.hpp>

#include "json.hpp"

using json = nlohmann::json;
using namespace boost;


class NetWorker {
    const std::string ip_address = "127.0.0.1"; // server address
    const unsigned int port = 8123;

public:
    NetWorker() : _service(), _ep(asio::ip::address::from_string(ip_address), port), _sock(_service) {
    }

    ~NetWorker() = default;

    // возвращает код ошибки, 0 - успех, 1 - не удалось подключиться к серверу
    int connect() {
       return 0;
    }

    void disconnect() {

    }

    int sendMessage(const std::string &request) {
        return 0;
    }

    int sendFile(const std::string &fileName) {
        return 0;
    }

private:
    asio::io_service _service;
    asio::ip::tcp::endpoint _ep;
    asio::ip::tcp::socket _sock;
};
