#pragma once

#include "object.h"

struct CheckListItem : public Object {
    CheckListItem(const std::string &t, const bool checked, size_t cli) : title(t), isChecked(checked),
                                                                          checkListId(cli) {
    }

    json toJson() override {
        json result;
        result["id"] = id;
        result["title"] = title;
        result["is_checked"] = isChecked;
        result["check_list_id"] = checkListId;
        return result;
    }

    void fromJson(json data) override {
        id = data["id"];
        title = data["title"];
        isChecked = data["is_checked"];
        checkListId = data["check_list_id"];
    }

    std::string title;
    bool isChecked;

    size_t checkListId;
};


