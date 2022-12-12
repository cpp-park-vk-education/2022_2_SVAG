#pragma once

#include <QString>

#include "object.h"

struct QCheckListItem : public Object {
    QCheckListItem(const std::string &t, const bool checked, size_t cli) : title(t), isChecked(checked),
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

    void fromJson(json) override {

    }

    std::string title;
    bool isChecked;

    size_t checkListId;
};


