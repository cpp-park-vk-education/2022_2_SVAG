#pragma once

#include <QtWidgets>

#include "mainwindow.h"
#include "user.h"
#include "object.h"
#include "board.h"

class GuiWorker : public QObject {
Q_OBJECT
public:
    explicit GuiWorker(QObject *parent = nullptr) : QObject(parent) {
        _mainWindow.showMaximized();

        // connect
        // object
        connect(&_mainWindow, &MainWindow::addObjectSignal, this, &GuiWorker::addObjectSignal);
        connect(&_mainWindow, &MainWindow::delObjectSignal, this, &GuiWorker::delObjectSignal);
        connect(&_mainWindow, &MainWindow::updateObjectSignal, this, &GuiWorker::updateObjectSignal);

        // user
        connect(&_mainWindow, &MainWindow::authUserSignal, this, &GuiWorker::authUserSignal);
        connect(&_mainWindow, &MainWindow::registerUserSignal, this, &GuiWorker::registerUserSignal);
        connect(&_mainWindow, &MainWindow::logoutSignal, this, &GuiWorker::logoutSignal);
        connect(&_mainWindow, &MainWindow::addUserSignal, this, &GuiWorker::addUserSignal);
    }

    GuiWorker(const GuiWorker &) = delete;

    GuiWorker(GuiWorker &&) = delete;

    GuiWorker &operator=(const GuiWorker &) = delete;

    GuiWorker &operator=(GuiWorker &&) = delete;

    ~GuiWorker() override {
        _mainWindow.close();
    }

signals:

    // user
    void authUserSignal(User &);

    void registerUserSignal(User &);

    void addUserSignal(User &, const size_t);

    void logoutSignal();

    // object
    void addObjectSignal(Object &, ObjType);

    void delObjectSignal(size_t, ObjType);

    void updateObjectSignal(Object &, ObjType);


private:
    MainWindow _mainWindow;
};
