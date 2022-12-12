#pragma once

#include <QString>

#include <cstddef>
#include <utility>
#include <iostream>

#include "object.h"
#include "qcolumn.h"

struct QBoard : public Object {
    QBoard(const std::string &n = "", const std::string &desc = "", const std::string &bg = "") : name(n),
                                                                                                  caption(desc),
                                                                                                  background(bg) {}

    json toJson() override {
        json result;
        result["id"] = id;
        result["name"] = name;
        result["caption"] = caption;
        result["background"] = background;
        return result;
    }

    void fromJson(json jsBoard) override {
        id = jsBoard["id"];
        name = jsBoard["name"];
        caption = jsBoard["caption"];
        background = jsBoard["background"];
    }

    std::string name;
    std::string caption;
    std::string background;
    std::vector<QColumn> columns;
};
