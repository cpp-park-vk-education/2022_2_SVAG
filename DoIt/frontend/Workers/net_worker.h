#pragma once

#include <iostream>
#include <fstream>

#include <QDebug>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "Lib/json.hpp"

using json = nlohmann::json;
using namespace boost;


class NetWorker {
    const std::string ip_address = "127.0.0.1"; // server address
    const unsigned int port = 8123;

public:
    NetWorker() : _service(), _ep(asio::ip::address::from_string(ip_address), port), _sock(_service), _started(true) {
//        connect();
    }

    ~NetWorker() = default;

    void connect() {
        _sock.connect(_ep);
    }

    void disconnect() {
        _sock.close();
    }

    void sendMessage(const std::string &request, int &err_code) {
        err_code = 0;
        try {
            _sock.connect(_ep);
        } catch (boost::system::system_error &err) {
            err_code = 1;
            return;
        }
        asio::write(_sock, asio::buffer(request), asio::transfer_all());
        _sock.close();
    }

    std::string getMessage(int &err_code) {
        err_code = 0;
        try {
            _sock.connect(_ep);
        } catch (boost::system::system_error &err) {
            err_code = 1;
            return "";
        }
        size_t bytes = boost::asio::read(_sock, asio::buffer(_buff),
                                         boost::bind(&NetWorker::read_complete, this, _buff, _1, _2));
        std::string msg(_buff, bytes - 1); // -1 to remove \n
        _sock.close();

        return msg;
    }

    void sendFile(const std::string &fileName) {
        std::ifstream input(fileName, std::ios::binary);
        std::string buf(std::istreambuf_iterator<char>(input), {});
        connect();
        _sock.write_some(asio::buffer(buf.data(), buf.size()));
        disconnect();
        input.close();
        std::cout << "File sent.\n";
    }

private:
    size_t read_complete(char *buff, const system::error_code &err, size_t bytes) {
        if (err) return 0;
        bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;
        return found ? 0 : 1;
    }

    void write(const std::string &msg) {
        _sock.write_some(asio::buffer(msg));
    }

private:
    asio::io_service _service;
    asio::ip::tcp::endpoint _ep;
    asio::ip::tcp::socket _sock;

    char _buff[1024];
    size_t _already_read;

    bool _started;
};
