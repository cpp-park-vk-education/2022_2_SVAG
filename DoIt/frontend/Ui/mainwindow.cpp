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

    QWidget *centralWidget = _ui->Draw();

    _ui->setStyleSheet(centralWidget);

    _ui->setCentralWidget(centralWidget);
}


void MainWindow::setStyleSheet(QWidget *widget) const {
    widget->setStyleSheet(QString::fromUtf8
                                (
                                    "QWidget#hBoxWidget_1,\n"
                                    "QWidget#hBoxWidget_2,\n"
                                    "QWidget#hBoxWidget_3 \n"
                                    "{\n"
                                    "	background-color: silver;\n"
                                    "	border-radius: 10px;\n"
                                    "}\n"
                                    "\n"
                                    "QLineEdit {\n"
                                    "	margin-top: 2px;\n"
                                    "    border-radius: 5px;\n"
                                    "    padding: 2 8px;\n"
                                    "    selection-background-color: darkgray;\n"
                                    "	background: transparent;\n"
                                    "}\n"
                                    "\n"
                                    "QLineEdit:focus {\n"
                                    "	border: 1px solid blue;\n"
                                    "	background-color: white;\n"
                                    "}\n"
                                    "\n"
                                    "QTextEdit {\n"
                                    "	margin-top: 2px;\n"
                                    "    border-radius: 5px;\n"
                                    "	background-color: white;\n"
                                    "}\n"
                                    "\n"
                                    "QTextEdit:hover {\n"
                                    "	background-color: rgb(250, 245, 245);\n"
                                    "}\n"
                                    ""
                                )
                            );
}


MainWindow::~MainWindow() {
    qDebug() << "~MainWindow()";
    delete _ui;
}


Menu MainWindow::CreateNavbar() {}


Menu MainWindow::CreateMenu() {}


QWidget* MainWindow::Draw() const {
    // Cards //
    // First column
    Card card11("Title card 1", "Caption card 1");
    Card card12("Title card 2", "Caption card 2", QDateTime(QDate(2022, 12, 11), QTime(8, 0)));
    QVector<Card> cardFirstCol;
    cardFirstCol.append(card11);
    cardFirstCol.append(card12);

    // Second column
    Card card21("Title card 1", "Caption card 1", QVector<QString>("Tag for card 1"));
    Card card22("Title card 2", "Caption card 2", QVector<QString>("Tag for card 2"), QDateTime(QDate(2022, 12, 11), QTime(12, 0)));
    QVector<Card> cardSecondCol;
    cardSecondCol.append(card21);
    cardSecondCol.append(card22);


    // Columns //
    Column col1("Col 1", cardFirstCol);
    Column col2("Col 2 empty");
    Column col3("Col 3", cardSecondCol);
    QVector<Column> columns;
    columns.append(col1);
    columns.append(col2);
    columns.append(col3);

    // Board //
    Board board("Board", columns);

    // Draw Board //
    return board.Draw();
}
