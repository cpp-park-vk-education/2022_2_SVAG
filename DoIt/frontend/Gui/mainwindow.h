#pragma once

#include <iostream>

#include "board.h"
#include "board_widget.h"
#include "menu.h"

#include <QMainWindow>

class MainWindow : public QMainWindow, IDraw {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  QWidget *Draw() const override;

  void showBoards(const std::vector<Board> &boards) {
    std::cout << "MainWindow::showBoards()\n";
    // convert model data in ui data
    for (auto &board : boards) {
      BoardWidget boardW(QString(board.name.data()));
      for (auto &column : board.columns) {
        ColumnWidget columnW(QString(column.name.data()));
        for (auto &card : column.cards) {
          CardWidget cardW(QString(card.name.data()),
                           QString(card.caption.data()));
          columnW.addCard(cardW);
        }
        boardW.addColumn(columnW);
      }
      boardManager.addBoard(boardW);
    }

    // draw ui data
    QHBoxLayout *mainLayout =
        centralWidget()->findChild<QHBoxLayout *>("mainLayout");
    QWidget *newWidget = findChild<QWidget *>("newWidget");
    QWidget *widget = nullptr;
    if (!boardManager.empty()) {
      widget = boardManager.first().Draw();
    } else {
      widget = new QLabel("No Boards :(");
    }

    mainLayout->removeWidget(newWidget);
    mainLayout->insertWidget(1, widget, Qt::AlignLeft);
  }

  void showLoadAllData() {}

public slots:
  void onCreateBoardClicked() {
    QHBoxLayout *mainLayout =
        centralWidget()->findChild<QHBoxLayout *>("mainLayout");

    QWidget *widget = boardManager.first().Draw();

    QWidget *newWidget = findChild<QWidget *>("newWidget");
    mainLayout->removeWidget(newWidget);
    mainLayout->insertWidget(1, widget, Qt::AlignLeft);

    qInfo() << mainLayout->children();
  }

private:
  Navbar navbar;
  Menu menu;
  BoardManager boardManager;

  QWidget *defaultBoardWidget = new QWidget();

  void resizeEvent(QResizeEvent *event) override;
};
