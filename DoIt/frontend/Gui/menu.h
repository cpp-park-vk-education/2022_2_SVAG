#pragma once

#include "main_interfaces.h"

#include <QLabel>
#include <QComboBox>
#include <QPushButton>

class Navbar;
class Menu;


class IMenu : public IDraw {
public:
    virtual ~IMenu() = default;

    virtual QWidget* Draw() const = 0;
};


class Navbar : public IMenu {
public:
    Navbar() = default;
    ~Navbar() = default;

    virtual QWidget* Draw() const override;
};


class Menu : public IMenu {
public:
    Menu() = default;
    ~Menu() = default;

    virtual QWidget* Draw() const override;
};
