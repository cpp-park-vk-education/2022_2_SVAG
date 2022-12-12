#pragma once

#include <QString>

#include "object.h"
#include "qtag.h"
#include "qcheck_list.h"

struct QCard : public Object {
    QCard(const std::string &t = "", const std::string &d = "", size_t ci = 0) : name(t), description(d),
                                                                                 columnId(ci) {
    }

    json toJson() override {
        json result;
        result["id"] = id;
        result["name"] = name;
        result["caption"] = description;
        result["column_id"] = columnId;
        return result;
    }

    void fromJson(json jsCard) override {
        id = jsCard["id"];
        name = jsCard["name"];
        description = jsCard["caption"];
        columnId = jsCard["column_id"];
    }

    std::string name;
    std::string description;
    size_t columnId;

    std::vector<QTag> tags;
    std::vector<QCheckList> checkLists;
};
