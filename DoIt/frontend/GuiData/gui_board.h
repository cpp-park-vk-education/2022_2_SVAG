#pragma once

#include <QString>

#include <cstddef>
#include <utility>

#include "gui_column.h"

struct GuiBoard {
    GuiBoard(QString &n, QString &bg) : name(n), bgPath(bg) {}

    QString name;
    QString bgPath;
};
