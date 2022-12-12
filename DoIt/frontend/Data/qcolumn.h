#pragma once

#include <QString>

#include "object.h"
#include "qcard.h"

struct QColumn : public Object {
    QColumn(std::string n = "", size_t di = 0) : name(n), boardId(di) {}

    json toJson() override {
        json result;
        result["id"] = id;
        result["name"] = name;
        result["board_id"] = boardId;
        return result;
    }

    void fromJson(json jsColumn) override {
        id = jsColumn["id"];
        name = jsColumn["name"];
        boardId = jsColumn["board_id"];
    }

    std::string name;

    std::vector<QCard> cards;

    size_t boardId;
};
