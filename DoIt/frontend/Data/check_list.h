#pragma once

#include <QString>

#include "check_list_item.h"
#include "object.h"

struct QCheckList : public Object {
    QCheckList(const std::string &t, size_t ci) : title(t), cardId(ci) {
    }


    json toJson() const override {
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


