#pragma once

#include "ui_mainwindow.h"
#include "qboard.h"
#include "user.h"
#include "menu.h"
#include "board.h"

#include <QMainWindow>
#include <QTimer>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow, Menu {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    Menu CreateNavbar();

    Menu CreateMenu();

    void Draw() const override;

private:
    Ui::MainWindow *_ui;

    Menu *navbar;
    Menu *menu;
    BoardManager boardManager;
};
