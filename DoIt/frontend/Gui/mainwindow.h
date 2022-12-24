#pragma once

#include <iostream>

#include "board.h"
#include "board_widget.h"
#include "menu.h"

#include <QInputDialog>
#include <QMainWindow>

class MainWindow : public QMainWindow, IDraw {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  QWidget *Draw() const override;

  void showBoards(const std::vector<Board> &boards) {
    boardManager.clear();

    // convert model data in ui data
    for (auto &board : boards) {
      BoardWidget boardW(QString(board.name.data()));
      boardW.setID(board.id);
      for (auto &column : board.columns) {
        ColumnWidget columnW(QString(column.name.data()));
        columnW.setColNum(column.id);
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
    QWidget *newWidget = nullptr;
    BoardWidget boardW = boardManager.getBoards()[curBoardIndex];
    if (!boardManager.empty()) {
      newWidget = boardW.Draw();
    } else {
      newWidget = new QLabel("No Boards :(");
    }

    QHBoxLayout *mainLayout = findChild<QHBoxLayout *>("mainLayout");
    mainLayout->removeWidget(curWidget);
    delete curWidget;
    mainLayout->insertWidget(1, newWidget, Qt::AlignLeft);
    curWidget = newWidget;

    // connections
    QVector<QPushButton *> addCardLabels =
        findChildren<QPushButton *>("addCardLabel");

    auto it = addCardLabels.begin();
    for (auto columnW : boardW.getColumns()) {
      connect(*it, &QPushButton::clicked,
              [columnW, this] { onAddCardClicked(columnW.getColNum()); });
      ++it;
    }

    QPushButton *addColLabel = findChild<QPushButton *>("addColumnLabel");
    connect(addColLabel, &QPushButton::clicked,
            [boardW, this] { onAddColumnClicked(boardW.getID()); });

    // For Navbar //
    QComboBox *chooseBoard = findChild<QComboBox *>("chooseBoard");
    chooseBoard->clear();
    for (auto &bW : boardManager.getBoards()) {
      chooseBoard->addItem(QIcon("Gui/resources/background/default_board.jpg"),
                           bW.getName());
    }
    chooseBoard->setIconSize(QSize(40, 40));
    chooseBoard->setCurrentIndex(curBoardIndex);

    connect(chooseBoard, &QComboBox::activated, this,
            &MainWindow::onBoardChanged);

    resize();
  }

  void showLoadAllData() {}

public slots:
  void onAddBoardClicked() {
    QString name = QInputDialog::getText(this, "Добавление доски", "Название");

    Board board;
    board.name = name.toStdString();

    addObjectSignal(board, BOARD);
  }

  void onAddCardClicked(int col_id) {
    QString name =
        QInputDialog::getText(this, "Добавление карточки", "Название");

    Card card;

    card.name = name.toStdString();
    card.columnId = col_id;

    addObjectSignal(card, CARD);
  }

  void onAddColumnClicked(int board_id) {
    QString name =
        QInputDialog::getText(this, "Добавление колонки", "Название");

    Column col;

    col.name = name.toStdString();
    col.boardId = board_id;

    addObjectSignal(col, COLUMN);
  }

  void onBoardChanged(int index) {
    BoardWidget boardW = boardManager.getBoards()[index];
    QWidget *newWidget = boardW.Draw();
    QHBoxLayout *mainLayout = findChild<QHBoxLayout *>("mainLayout");
    mainLayout->removeWidget(curWidget);
    delete curWidget;
    mainLayout->insertWidget(1, newWidget, Qt::AlignLeft);
    curWidget = newWidget;
    resize();

    QVector<QPushButton *> addCardLabels =
        findChildren<QPushButton *>("addCardLabel");

    // connections
    auto it = addCardLabels.begin();
    for (auto columnW : boardManager.getBoards()[index].getColumns()) {
      connect(*it, &QPushButton::clicked,
              [columnW, this] { onAddCardClicked(columnW.getColNum()); });
      ++it;
    }

    curBoardIndex = index;
    QPushButton *addColLabel = findChild<QPushButton *>("addColumnLabel");
    connect(addColLabel, &QPushButton::clicked,
            [boardW, this] { onAddColumnClicked(boardW.getID()); });
  }

signals:
  void addObjectSignal(Object &, ObjType);

private:
  Navbar navbar;
  Menu menu;
  BoardManager boardManager;

  int curBoardIndex = 0;

  QWidget *curWidget = new QLabel("Load Boards.....");

  void resizeEvent(QResizeEvent *event) override;
  void resize();
};
