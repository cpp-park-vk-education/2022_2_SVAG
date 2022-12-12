#include "mainwindow.h"
#include "board.h"

#include <QDebug>
#include <QVector>
#include <QString>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include <thread>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _ui(new Ui::MainWindow) {
    qDebug() << "MainWindow()";
    _ui->setupUi(this);

// Cards
    // First column
    Card card11("Title card 1", "Caption card 1");
    Card card12("Title card 2", "Caption card 2", QDateTime(QDate(2022, 12, 11), QTime(8, 0)));
    QVector<Card> cardFirstCol;
    cardFirstCol.append(card11);
    cardFirstCol.append(card12);

    // Second column
    Card card21("Title card 1", "Caption card 1", QVector<QString>());
    Card card22("Title card 2", "Caption card 2", QVector<QString>(),
                QDateTime(QDate(2022, 12, 11), QTime(12, 0)));
    QVector<Card> cardSecondCol;
    cardSecondCol.append(card21);
    cardSecondCol.append(card22);


    // Columns
    Column col1("Col 1", cardFirstCol);
    Column col2("Col 2 empty");
    Column col3("Col 3", cardSecondCol);
    QVector<Column> columns;
    columns.append(col1);
    columns.append(col2);
    columns.append(col3);


    Board board("QBoard", columns);

    // qInfo() << (board.getColumns()[0]).getCards()[0].GetText();

    // QBoard
    qInfo() << board.GetText();
    qInfo() << board.columnCount();
}

MainWindow::~MainWindow() {
    qDebug() << "~MainWindow()";
    delete _ui;
}

Menu MainWindow::CreateNavbar() {}

Menu MainWindow::CreateMenu() {}

void MainWindow::Draw() const {}
