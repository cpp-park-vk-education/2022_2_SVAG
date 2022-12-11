#pragma once

#include <QString>

struct GuiTag {
    GuiTag(const QString &n, const QString &c, size_t ci) : name(n), color(c), cardId(ci) {
    }

    QString name;
    QString color;

    size_t cardId;
};
