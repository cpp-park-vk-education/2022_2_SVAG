#pragma once

#include <QMainWindow>

#include "menu.h"

class MainWindow : public QMainWindow, Menu
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Menu CreateNavbar();
    Menu CreateMenu();
    void Draw() const override;

private:
    Menu* navbar;
    Menu* menu;
    // std::vector<Board> boards;
};
