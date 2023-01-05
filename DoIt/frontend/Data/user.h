#pragma once

#include <cstddef>
#include <utility>

#include "object.h"
#include "column.h"

struct User : public Object {
    User(const std::string &un, const std::string &p = "")
            : username(un), password(p) {}

    User(const std::string &un, const std::string &p, const std::string &e, const std::string &ap)
            : username(un), password(p), email(e), avatarPath(ap) {}

    json toJson() override {
        json result;
        result["id"] = id;
        result["username"] = username;
        result["password"] = password;
        result["email"] = email;
        result["avatarPath"] = avatarPath;
        return result;
    }

    void fromJson(json data) override {
        id = data["id"];
        username = data["username"];
        password = data["password"];
        email = data["email"];
        avatarPath = data["avatarPath"];
    }

    std::string username;
    std::string password;
    std::string email;
    std::string avatarPath;
};
