#pragma once

#include <cstddef>
#include <utility>

#include "object.h"
#include "column.h"

struct Board : public Object {
    Board(const std::string &n, const std::string &bg) : name(n), bgPath(bg) {}

    json toJson() override {
        json result;
        result["id"] = id;
        result["name"] = name;
        result["bg_path"] = bgPath;
        return result;
    }

    void fromJson(json data) override {
        id = data["id"];
        name = data["name"];
        bgPath = data["bg_path"];
    }

    std::string name;
    std::string bgPath;

    std::vector<Column> columns;
};
