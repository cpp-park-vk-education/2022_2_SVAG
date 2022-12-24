#include "gui_manager.h"

GuiManager::GuiManager(QObject *parent) : QObject(parent) {
    _authWindow.show();

    // connections
    // from main window
    connect(&_mainWindow, &MainWindow::addObjectSignal, this, &GuiManager::addObjectSignal);

    // from auth window
    connect(&_authWindow, &AuthWindow::authSignal, this, &GuiManager::authSignal);

    // from reg window
    connect(&_regWindow, &RegWindow::regSignal, this, &GuiManager::regSignal);
    connect(&_authWindow, &AuthWindow::openRegSignal, this, &GuiManager::openRegSlot);
    connect(&_regWindow, &RegWindow::openAuthSignal, this, &GuiManager::openAuthSlot);
}

GuiManager::~GuiManager() {
    _mainWindow.close();
    _authWindow.close();
    _regWindow.close();
}

void GuiManager::showBoards(const std::vector<Board> &boards) {
    _mainWindow.showBoards(boards);
}

void GuiManager::showLoadAllData() {
    _authWindow.close();
    _regWindow.close();
    _mainWindow.show();
    _mainWindow.showLoadAllData();
}

// public slots
void GuiManager::openRegSlot() {
    _authWindow.close();
    _regWindow.show();
}

void GuiManager::openAuthSlot() {
    _regWindow.close();
    _authWindow.show();
}
