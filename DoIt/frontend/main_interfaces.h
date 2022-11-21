#pragma once

#include <iostream>
#include <string>
//#include <chrono>
#include <QTime>


class IDraw {
public:
    virtual ~IDraw() = default;

    virtual void Draw() const = 0;
};


class IText {
public:
    virtual ~IText() = default;

    virtual void SetText(const std::string& text) const = 0;
    virtual std::string GetText() const = 0;
};


class IDate {
    public:
    virtual ~IDate() = default;

    virtual void SetDate(QTime date) const = 0;
    virtual QTime GetText() const = 0;
};
