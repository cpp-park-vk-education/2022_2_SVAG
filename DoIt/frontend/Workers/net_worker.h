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
        qDebug() << "Socket connected";
    }

    void disconnect() {
        _sock.close();
        qDebug() << "Socket disconnected";
    }
//    void loop() {
//        while (_started) {
////            json data =
//            write_request();
//            read_answer();
//            int millis = rand() % 4000;
//            std::cout << "do ping " << millis << " ms" << std::endl;
//            boost::this_thread::sleep(boost::posix_time::millisec(millis));
//        }
//    }

    void sendMessage(const std::string &request, int &err_code) {
        err_code = 0;
        try {
            _sock.connect(_ep);
        } catch (boost::system::system_error &err) {
            err_code = 1;
            return;
        }
        _sock.write_some(asio::buffer(request));
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
        qDebug() << "sendFile()";
        std::cout << "FileName =" << fileName << std::endl;

//        std::ifstream input(fileName, std::ios::binary);
        std::ifstream input(fileName, std::ios::binary);
//        std::string buf(std::istreambuf_iterator<char>(input), {});
        std::string buf(std::istreambuf_iterator<char>(input), {});
//        std::cout << buf << std::endl;
//        std::string ms = "gg";
        std::cout << "Sending file to server...\n";
//        _sock.send(asio::buf(buf, buf.size()));
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

    void write_request() {
        write("ping\n");
    }
//
//    void read_answer() {
//        _already_read = 0;
//        asio::read(_sock, asio::buffer(_buff),
//                   boost::bind(&NetWorker::read_complete, this, _1, _2));
//        process_msg();
//    }

//    void process_msg() {
//        std::string msg(_buff, _already_read);
////        if ( msg.find("login ") == 0) on_login();
//        if (msg.find("ping") == 0) on_ping(msg);
////        else if ( msg.find("clients ") == 0) on_clients(msg);
//        else std::cerr << "invalid msg " << msg << std::endl;
//    }

//    void on_ping(const std::string &msg) {
//        std::istringstream in(msg);
//        std::string answer;
//        in >> answer >> answer;
//        if (answer == "data_changed")
//            do_ask_changes();
//    }

//    void do_ask_changes() {
//        write("ask_changes\n");
//        read_answer();
//    }

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
