#pragma once

#include <QString>

#include "object.h"
#include "qcheck_list_item.h"

struct QCheckList : public Object {
    QCheckList(const std::string &t, size_t ci) : title(t), cardId(ci) {
    }


    json toJson() override {
        json result;
        result["id"] = id;
        result["name"] = title;
        result["card_id"] = cardId;
        return result;
    }

    void fromJson(json) override {

    }

    std::string title;

    std::vector<QCheckListItem> items;

    size_t cardId;
};


