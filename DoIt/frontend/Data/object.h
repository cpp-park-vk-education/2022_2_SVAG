#pragma once

#include <cstddef>
#include "Lib/json.hpp"

using json = nlohmann::json;

enum ObjType {
    BOARD, COLUMN, CARD, TAG, CHECK_LIST, CHECK_LIST_ITEM
};

struct Object {
    size_t id;

    Object() : id(0) {}

    Object(size_t i) : id(i) {}

    virtual ~Object() = default;

    virtual json toJson() = 0;

    virtual void fromJson(json) = 0;
};
