#pragma once

#include <QtWidgets>

#include <iostream>

#include "auth_window.h"
#include "mainwindow.h"
#include "reg_window.h"

#include "board.h"

class GuiManager : public QObject {
Q_OBJECT
public:
    explicit GuiManager(QObject *parent = nullptr);

    GuiManager(const GuiManager &) = delete;

    GuiManager(GuiManager &&) = delete;

    GuiManager &operator=(const GuiManager &) = delete;

    GuiManager &operator=(GuiManager &&) = delete;

    ~GuiManager() override;

    void showBoards(const std::vector<Board> &boards);

    void showLoadAllData();

public slots:

    void openRegSlot();

    void openAuthSlot();

signals:

    void authSignal(const User &);

    void regSignal(const User &);

    void addObjectSignal(Object &, ObjType);

private:
    MainWindow _mainWindow;
    AuthWindow _authWindow;
    RegWindow _regWindow;
};
