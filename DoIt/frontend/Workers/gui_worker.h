#pragma once

#include <QtWidgets>

#include "mainwindow.h"
#include "user.h"
#include "object.h"

class GuiWorker : public QObject {
Q_OBJECT
public:
    explicit GuiWorker(QObject *parent = nullptr) : QObject(parent) {
        _mainWindow.showMaximized();
    }

    GuiWorker(const GuiWorker &) = delete;

    GuiWorker(GuiWorker &&) = delete;

    GuiWorker &operator=(const GuiWorker &) = delete;

    GuiWorker &operator=(GuiWorker &&) = delete;

    ~GuiWorker() override {
        _mainWindow.close();
    }

public slots:
    

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
