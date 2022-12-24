#pragma once

#include <fstream>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "Lib/json.hpp"

using json = nlohmann::json;
using namespace boost;

class NetManager {
    const std::string ip_address = "127.0.0.1"; // server address
    const unsigned int port = 8001;

public:
    NetManager()
            : _service(), _ep(asio::ip::address::from_string(ip_address), port),
              _sock(_service), _ping_sock(_service), started_(true) {}

    ~NetManager() = default;

    void pingLoop();

    void connect();

    void disconnect();

    void sendMessage(const std::string &request, int &err_code);

    std::string getMessage(int &err_code);

    void sendFile(const std::string &fileName, int &err_code);

private:
    static size_t read_complete(char *buff, const system::error_code &err,
                                size_t bytes);

private:
    asio::io_service _service;
    asio::ip::tcp::endpoint _ep;
    asio::ip::tcp::socket _sock;
    asio::ip::tcp::socket _ping_sock;

    char _buff[1024];
    char _buff_ping[1024];
    int already_read_;
    bool started_;
};
