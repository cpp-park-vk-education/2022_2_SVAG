#pragma once

#include <cstddef>
#include <utility>

#include "column.h"
#include "object.h"

struct User : public Object {
  User(const std::string &un="", const std::string &p = "")
            : username(un), password(p) {}

  User(const std::string &un, const std::string &p, const std::string &e, const std::string &ap)
            : username(un), password(p), email(e), avatarPath(ap) {}

    json toJson() const override {
        json result;
        result["id"] = id;
        result["username"] = username;
        result["password"] = password;
        result["email"] = email;
        result["avatar"] = avatarPath;
        return result;
    }

    void fromJson(json) override {

    }

    std::string username;
    std::string password;
    std::string email;
    std::string avatarPath;
};
