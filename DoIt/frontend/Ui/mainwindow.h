#pragma once

#include "ui_mainwindow.h"
#include "qboard.h"

#include <QMainWindow>
#include <QTimer>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *_ui;
};
