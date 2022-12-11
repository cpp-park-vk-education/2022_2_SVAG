#pragma once

#include <QString>

struct GuiCheckListItem {
    GuiCheckListItem(const QString &t, const bool checked, size_t cli) : title(t), isChecked(checked),
                                                                      checkListId(cli) {
    }

    QString title;
    bool isChecked;

    size_t checkListId;
};


