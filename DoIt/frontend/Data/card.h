#pragma once

#include "object.h"
#include "tag.h"
#include "check_list.h"

struct Card : public Object {
    Card(const std::string &t, const std::string &d, size_t ci) : title(t), description(d), columnId(ci) {
    }

    json toJson() override {
        json result;
        result["id"] = id;
        result["title"] = title;
        result["description"] = description;
        result["column_id"] = columnId;
        return result;
    }

    void fromJson(json data) override {
        id = data["id"];
        title = data["title"];
        description = data["description"];
        columnId = data["column_id"];
    }

    std::string title;
    std::string description;

    std::vector<Tag> tags;
    std::vector<CheckList> checkLists;

    size_t columnId;
};
