#pragma once

#include <QtWidgets>

#include <iostream>

#include "auth_window.h"
#include "mainwindow.h"
#include "reg_window.h"


class GuiManager : public QObject {
  Q_OBJECT
public:
  explicit GuiManager(QObject *parent = nullptr) : QObject(parent) {
    _authWindow.show();

    connect(&_authWindow, &AuthWindow::authSignal, this,
            &GuiManager::authSignal);
    connect(&_regWindow, &RegWindow::regSignal, this,
            &GuiManager::regSignal);
    connect(&_authWindow, &AuthWindow::openRegSignal, this,
            &GuiManager::openRegSlot);
    connect(&_regWindow, &RegWindow::openAuthSignal, this,
            &GuiManager::openAuthSlot);
  }

  GuiManager(const GuiManager &) = delete;

  GuiManager(GuiManager &&) = delete;

  GuiManager &operator=(const GuiManager &) = delete;

  GuiManager &operator=(GuiManager &&) = delete;

  ~GuiManager() override {
    _mainWindow.close();
  }

  void showBoards(const std::vector<Board> &boards) {
    _mainWindow.showBoards(boards);
  }

  void showLoadAllData() {
    _authWindow.close();
    _regWindow.close();
    _mainWindow.show();
    _mainWindow.showLoadAllData();
  }

public slots:
  void openRegSlot() {
    _authWindow.close();
    _regWindow.show();
  }

  void openAuthSlot() {
    _regWindow.close();
    _authWindow.show();
  }


signals:
  void authSignal(const User &user);
  void regSignal(const User &user);

private:
  MainWindow _mainWindow;
  AuthWindow _authWindow;
  RegWindow _regWindow;
};
