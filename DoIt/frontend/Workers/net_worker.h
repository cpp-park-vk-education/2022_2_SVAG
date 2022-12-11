#pragma once

#include <iostream>
#include <fstream>

#include <boost/asio.hpp>

#include "Lib/json.hpp"

using json = nlohmann::json;
using namespace boost;


class NetWorker {
    const std::string ip_address = "127.0.0.1"; // server address
    const unsigned int port = 8123;

public:
    NetWorker() : _service(), _ep(asio::ip::address::from_string(ip_address), port), _sock(_service) {
    }

    ~NetWorker() = default;

    void connect() {
        _sock.connect(_ep);
    }

    void disconnect() {
        _sock.close();
    }

    void sendRequest(const std::string &request) {
        _sock.connect(_ep);
        _sock.write_some(asio::buffer(request));
        _sock.close();
    }

    void sendFile(const std::string &fileName) {
        std::ifstream input(fileName, std::ios::binary);
        std::string buf(std::istreambuf_iterator<char>(input), {});
        connect();
        _sock.write_some(asio::buffer(buf.data(), buf.size()));
        disconnect();
        input.close();
    }

private:
    asio::io_service _service;
    asio::ip::tcp::endpoint _ep;
    asio::ip::tcp::socket _sock;
};
