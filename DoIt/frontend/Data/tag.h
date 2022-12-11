#pragma once

#include "object.h"

struct Tag : public Object {
    Tag(const std::string &n, const std::string &c, size_t ci) : name(n), color(c), cardId(ci) {
    }


    json toJson() override {
        json result;
        result["id"] = id;
        result["name"] = name;
        result["color"] = color;
        result["card_id"] = cardId;
        return result;
    }

    void fromJson(json data) override {
        id = data["id"];
        name = data["name"];
        color = data["color"];
        cardId = data["card_id"];
    }

    std::string name;
    std::string color;

    size_t cardId;
};
