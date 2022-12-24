#pragma once

#include <QTime>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

#include <QScrollArea>
#include <QScrollBar>

class IDraw {
public:
    virtual ~IDraw() = default;

    virtual QWidget* Draw() const = 0;
};


class IText {
public:
    virtual ~IText() = default;

    virtual void SetText(const QString& _text) = 0;
    virtual QString GetText() const = 0;
};


class IDate {
    public:
    virtual ~IDate() = default;

    virtual void SetDate(QDateTime _date) = 0;
    virtual QDateTime GetDate() const = 0;
};
