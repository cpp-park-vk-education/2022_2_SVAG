#pragma once

#include <QString>

#include "gui_tag.h"
#include "gui_check_list.h"

struct GuiCard {
    GuiCard(const QString &t, const QString &d, size_t ci) : title(t), description(d), columnId(ci) {
    }

    QString title;
    QString description;

    size_t columnId;
};
