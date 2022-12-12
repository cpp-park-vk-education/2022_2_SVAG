#pragma once

#include <string>
#include <vector>

#include "main_interfaces.h"


class Item;
class Menu;


class Iitem : public IDraw {
public:
    virtual ~Iitem() = default;

    virtual void Draw() const = 0;
};


class IMenu : public IDraw {
public:
    virtual ~IMenu() = default;

    virtual void Draw() const = 0;
    virtual void AddItem(const Item& item) const = 0;
};


class ICreateMenus {
    public:
    virtual ~ICreateMenus() = default;

    virtual Menu CreateNavbar() const = 0;
    virtual Menu CreateMenu() const = 0;
};


class Item : public Iitem {
private:
    std::string caption;
};


class Menu : public Iitem, IMenu {
private:
    std::vector<Iitem> items;

public:
    void AddItem(const Item& item) const override;

    void Draw() const override;
};
