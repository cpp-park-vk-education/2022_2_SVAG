#pragma once

#include "object.h"
#include "check_list_item.h"

struct CheckList : public Object {
    CheckList(const std::string &t, size_t ci) : title(t), cardId(ci) {
    }


    json toJson() override {
        json result;
        result["id"] = id;
        result["title"] = title;
        result["card_id"] = cardId;
        return result;
    }

    void fromJson(json data) override {
        id = data["id"];
        title = data["title"];
        cardId = data["card_id"];
    }

    std::string title;

    std::vector<CheckListItem> items;

    size_t cardId;
};


