#pragma once

#include "object.h"
#include "card.h"

struct Column : public Object {
    Column(std::string n, size_t di) : name(n), deskId(di) {}

    json toJson() override {
        json result;
        result["id"] = id;
        result["name"] = name;
        result["desk_id"] = deskId;
        return result;
    }

    void fromJson(json data) override {
        id  = data["id"];
        name = data["name"];
        deskId = data["desk_id"];
    }

    std::string name;

    std::vector<Card> cards;

    size_t deskId;
};
