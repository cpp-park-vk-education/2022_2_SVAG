#pragma once

#include <QString>

#include "object.h"
#include "qtag.h"
#include "qcheck_list.h"

struct QCard : public Object {
    QCard(const std::string &t, const std::string &d, size_t ci) : title(t), description(d), columnId(ci) {
    }

    json toJson() override {
        json result;
        result["id"] = id;
        result["title"] = title;
        result["description"] = description;
        result["column_id"] = columnId;
        return result;
    }

    void fromJson(json) override {

    }

    std::string title;
    std::string description;
    tm deadline{};

    std::vector<QTag> tags;
    std::vector<QCheckList> checkLists;

    size_t columnId;
};
