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

  void pingLoop() {
    try {
      _ping_sock.connect(_ep);
      std::cout << "Ping Connect success\n";
    } catch (boost::system::system_error &err) {
      std::cout << "Ping Connect failed\n";
      return;
    }
    while (started_) {
      json js_ping;
      int err = 0;
      js_ping["cmd"] = "ping";
      asio::write(_ping_sock, asio::buffer(js_ping.dump() + "\n"), asio::transfer_all());

      size_t bytes = boost::asio::read(
          _ping_sock, asio::buffer(_buff_ping),
          boost::bind(&NetManager::read_complete, _buff_ping, _1, _2));
      std::string response(_buff_ping, bytes - 1); // -1 to remove \n

      json resp = json::parse(response);

      boost::this_thread::sleep(boost::posix_time::millisec(3000));
    }

    _ping_sock.close();
  }

  void connect() {
    try {
      _sock.connect(_ep);
      std::cout << "Connect success\n";
    } catch (boost::system::system_error &err) {
      std::cout << "Connect failed\n";
      throw err;
    }
  }

  void disconnect() { _sock.close(); }

  void sendMessage(const std::string &request, int &err_code) {
    err_code = 0;
    asio::write(_sock, asio::buffer(request), asio::transfer_all());
  }

  std::string getMessage(int &err_code) {
    err_code = 0;
    size_t bytes = boost::asio::read(
        _sock, asio::buffer(_buff),
        boost::bind(&NetManager::read_complete, _buff, _1, _2));
    std::string msg(_buff, bytes - 1); // -1 to remove \n
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
  static size_t read_complete(char *buff, const system::error_code &err,
                       size_t bytes) {
    if (err)
      return 0;
    bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;
    return found ? 0 : 1;
  }

private:
  asio::io_service _service;
  asio::ip::tcp::endpoint _ep;
  asio::ip::tcp::socket _sock;
  asio::ip::tcp::socket _ping_sock;

  char _buff[1024];
  char _buff_ping[1024];
  bool started_;
};
