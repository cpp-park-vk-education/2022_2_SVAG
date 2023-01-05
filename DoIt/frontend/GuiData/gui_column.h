#pragma once

#include <QString>

#include "gui_card.h"

struct GuiColumn {
    GuiColumn(const QString &n, size_t di) : name(n), deskId(di) {}

    QString name;

    size_t deskId;
};
