#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _ui(new Ui::MainWindow) {
    _ui->setupUi(this);

    // connect add buttons
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::addBoardSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::addColumnSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::addCardSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::addTagSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::addCheckListSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::addCheckListItemSlot);

    // connect del buttons
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::delBoardSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::delColumnSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::delCardSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::delTagSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::delCheckListSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::delCheckListItemSlot);

    // connect update buttons
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::updateBoardSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::updateColumnSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::updateCardSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::updateTagSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::updateCheckListSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::updateCheckListItemSlot);

    // connect user logic buttons
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::addUserSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::authSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::logoutSlot);
    connect(_ui->btn, &QPushButton::clicked, this, &MainWindow::registerSlot);
}

MainWindow::~MainWindow() {
    delete _ui;
}
