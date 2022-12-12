#pragma once

#include <QtWidgets>

#include "mainwindow.h"
#include "window.h"

#include "object.h"
#include "qboard.h"

class GuiWorker : public QObject {
Q_OBJECT
public:
    explicit GuiWorker(QObject *parent = nullptr) : QObject(parent) {
//        _mainWindow.showMaximized();
        _window.showMaximized();

        // to window
        connect(this, &GuiWorker::sendBoardsSignal, &_window, &Window::getBoardsSlot);
        connect(this, &GuiWorker::sendColumnsSignal, &_window, &Window::getColumnsSlot);
        connect(this, &GuiWorker::sendCardsSignal, &_window, &Window::getCardsSlot);

        // from window
        connect(&_window, &Window::getColumnSignal, this, &GuiWorker::getColumnSignal);
        connect(&_window, &Window::getCardsSignal, this, &GuiWorker::getCardsSignal);
    }

    GuiWorker(const GuiWorker &) = delete;

    GuiWorker(GuiWorker &&) = delete;

    GuiWorker &operator=(const GuiWorker &) = delete;

    GuiWorker &operator=(GuiWorker &&) = delete;

    ~GuiWorker() override {
//        qDebug() << "~GuiWorker()";
//        _mainWindow.close();
        _window.close();
    }


signals:

    void sendBoardsSignal(std::vector<QBoard> &boards);

    void sendColumnsSignal(std::vector<QColumn> &columns);

    void sendCardsSignal(std::vector<QCard> &cards);

    void getColumnSignal(size_t);

    void getCardsSignal(size_t);

private:
    MainWindow _mainWindow;
    Window _window;
};
