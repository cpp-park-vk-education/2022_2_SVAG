#pragma once

#include <QString>

#include "object.h"
#include "qcard.h"

struct QColumn : public Object {
    QColumn(std::string n, size_t di) : name(n), deskId(di) {}

    json toJson() override {
        json result;
        result["id"] = id;
        result["name"] = name;
        result["desk_id"] = deskId;
        return result;
    }

    void fromJson(json) override {

    }

    std::string name;

    std::vector<QCard> cards;

    size_t deskId;
};
