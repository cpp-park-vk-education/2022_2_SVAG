#pragma once

#include <QString>

#include <cstddef>
#include <utility>

#include "gui_column.h"

struct GuiUser {
    GuiUser(const QString &un, const QString &p = "")
            : username(un), password(p) {}

    GuiUser(const QString &un, const QString &p, const QString &e, const QString &ap)
            : username(un), password(p), email(e), avatarPath(ap) {}

    QString username;
    QString password;
    QString email;
    QString avatarPath;
};
