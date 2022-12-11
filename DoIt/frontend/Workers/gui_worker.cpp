#include "gui_worker.h"

GuiWorker::GuiWorker(QObject *parent) : QObject(parent) {
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
