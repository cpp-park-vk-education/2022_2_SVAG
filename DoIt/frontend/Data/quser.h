#pragma once

#include <QString>

#include <cstddef>
#include <utility>

#include "object.h"
#include "qcolumn.h"

struct QUser : public Object {
    QUser(const std::string &un, const std::string &p = "")
            : username(un), password(p) {}

    QUser(const std::string &un, const std::string &p, const std::string &e, const std::string &ap)
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

    void fromJson(json) override {

    }

    std::string username;
    std::string password;
    std::string email;
    std::string avatarPath;
};
