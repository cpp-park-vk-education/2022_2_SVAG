#pragma once

#include <QString>

#include "gui_check_list_item.h"

struct GuiCheckList {
    GuiCheckList(const QString &t, size_t ci) : title(t), cardId(ci) {
    }

    QString title;

    size_t cardId;
};


