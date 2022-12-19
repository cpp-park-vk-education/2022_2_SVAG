#pragma once

#include <fstream>
#include <iostream>

#include <QDebug>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "Lib/json.hpp"
#include "user.h"

using json = nlohmann::json;
using namespace boost;

class UserManager {

public:
  UserManager(NetManager &netManager) : _netManager(netManager) {}

  ~UserManager() = default;

  size_t userId() const { return _userId; }

  void authUser(const User &user) {
    json data = user.toJson();
    data["cmd"] = "auth";
    std::string request = data.dump();

    int err = 0;
    _netManager.connect();
    _netManager.sendMessage(request + "\n", err);
    std::string response = _netManager.getMessage(err);
    json resp = json::parse(response);
    _netManager.disconnect();
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

  void addUserSlot(User &user, const size_t boardId) {
    json data = user.toJson();
    data["cmd"] = "add user to board";
    data["board_id"] = boardId;
    std::string request = data.dump();

    int err = 0;
    _netManager.sendMessage(request + '\n', err);
  }

private:
  NetManager &_netManager;
  size_t _userId = 0;
};
