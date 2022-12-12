#pragma once

#include "ui_window.h"
#include "qboard.h"

#include <iostream>

#include <QMainWindow>
#include <QTimer>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow {
Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);

    ~Window() override;

public slots:

    void getBoardsSlot(std::vector<QBoard> &boards) {
        qDebug() << "getBoardsSlot()";
        _ui->boardInput->clear();
        board_ids.clear();
        for (auto board: boards) {
            _ui->boardInput->addItem(QString(board.name.data()));
            board_ids.push_back(board.id);
        }

        qDebug() << "was added : " << board_ids[_ui->boardInput->currentIndex()];

        emit getColumnSignal(board_ids[_ui->boardInput->currentIndex()]);
    }

    void getColumnsSlot(std::vector<QColumn> &columns) {
        qDebug() << "getColumnsSlot()";
        _ui->columnInput->clear();
        column_ids.clear();
        for (auto column: columns) {
            _ui->columnInput->addItem(QString(column.name.data()));
            column_ids.push_back(column.id);
        }

        if (columns.size() > 0) {
            emit getCardsSignal(column_ids[_ui->columnInput->currentIndex()]);
        } else {
            _ui->listWidget->clear();
        }
    }

    void getCardsSlot(std::vector<QCard> &cards) {
        qDebug() << "getCardsSlot()";
        _ui->listWidget->clear();
        card_ids.clear();
        for (auto &card: cards) {
            std::cout << card.name << std::endl;
            _ui->listWidget->addItem(QString(("name: " + card.name + " caption: " + card.description).data()));
            card_ids.push_back(card.id);
        }
    }

private slots:

    void boardChangedSlot(int col_idx) {
        qDebug() << "board changed" << col_idx;
        if (board_ids.size() > 0) {
            qDebug() << board_ids[_ui->boardInput->currentIndex()];
            emit getColumnSignal(board_ids[_ui->boardInput->currentIndex()]);
        }
    }

    void columnChangedSlot(int col_idx) {
//        qDebug() << "col changed" << col_idx;
        if (column_ids.size() > 0) {
            emit getCardsSignal(column_ids[_ui->columnInput->currentIndex()]);
        }
//        qDebug() << "col changed emmited";
    }

signals:

    void getColumnSignal(size_t id);

    void getCardsSignal(size_t);

private:
    Ui::Window *_ui;

    std::vector<size_t> board_ids;
    std::vector<size_t> column_ids;
    std::vector<size_t> card_ids;
};
