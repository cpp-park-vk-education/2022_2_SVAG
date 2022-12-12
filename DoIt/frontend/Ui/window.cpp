#include "window.h"

#include <QtWidgets>
#include <QString>
#include <QMessageBox>
#include <QComboBox>
#include <QThread>

Window::Window(QWidget *parent) : QMainWindow(parent), _ui(new Ui::Window) {
    qDebug() << "Window()";
    _ui->setupUi(this);

//    connect(_ui->columnInput, &QComboBox::currentIndexChanged, this, &Window::columnChangedSlot);
    connect(_ui->boardInput, SIGNAL(currentIndexChanged(int)), this, SLOT(boardChangedSlot(int)));
    connect(_ui->columnInput, SIGNAL(currentIndexChanged(int)), this, SLOT(columnChangedSlot(int)));
}

Window::~Window() {
    qDebug() << "~Window()";
    delete _ui;
}
