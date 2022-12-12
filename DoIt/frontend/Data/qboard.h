#pragma once

#include <QString>

#include <cstddef>
#include <utility>

#include "object.h"
#include "qcolumn.h"

struct QBoard : public Object {
    QBoard(const std::string &n = "", const std::string &bg = "") : name(n), bgPath(bg) {}

    json toJson() override {
        json result;
        result["id"] = id;
        result["name"] = name;
        result["bg_path"] = bgPath;
        return result;
    }

    void fromJson(json) override {

    }

    std::string name;
    std::string bgPath;
    std::vector<QColumn> columns;
};
