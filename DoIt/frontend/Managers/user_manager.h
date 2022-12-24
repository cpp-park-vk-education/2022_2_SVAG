#pragma once

#include <fstream>
#include <iostream>

#include <QDebug>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "Lib/json.hpp"

using json = nlohmann::json;
using namespace boost;

class UserManager {
public:
  UserManager(NetManager &netManager) : _netManager(netManager) {}

  ~UserManager() = default;

  size_t userId() const { return _userId; }

  void authUser(const User &user) {
    json data;
    data["cmd"] = "login";
    data["data"] = user.toJson();
    std::string request = data.dump();

    int err = 0;
    _netManager.connect();
    _netManager.sendMessage(request + "\n", err);
    std::string response = _netManager.getMessage(err);
    json resp = json::parse(response);
    _netManager.disconnect();

    _userId = resp["result"][0]["id"];
  }

  void regUser(const User &user) {
    json data = user.toJson();
    data["cmd"] = "register";
    std::string request = data.dump();

    int err = 0;
    _netManager.connect();
    _netManager.sendMessage(request + "\n", err);
    std::string response = _netManager.getMessage(err);
    json resp = json::parse(response);
    _netManager.disconnect();

    _userId = resp["result"][0]["id"];
  }

private:
  NetManager &_netManager;
  size_t _userId = 0;
};
