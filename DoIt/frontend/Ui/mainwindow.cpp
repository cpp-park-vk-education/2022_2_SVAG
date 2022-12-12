#include "mainwindow.h"

#include <QString>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include <thread>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _ui(new Ui::MainWindow) {
    qDebug() << "MainWindow()";
    _ui->setupUi(this);
}

MainWindow::~MainWindow() {
    qDebug() << "~MainWindow()";
    delete _ui;
}
