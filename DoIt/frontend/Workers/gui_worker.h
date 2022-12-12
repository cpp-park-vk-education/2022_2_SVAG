#pragma once

#include <QtWidgets>

#include "mainwindow.h"

#include "object.h"
#include "qboard.h"

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
//        qDebug() << "~GuiWorker()";
        _mainWindow.close();
    }


private:
    MainWindow _mainWindow;
};
