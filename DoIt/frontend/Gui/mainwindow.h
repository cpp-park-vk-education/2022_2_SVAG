#pragma once

#include <iostream>

#include "board.h"
#include "boardwidgetmanager.h"
#include "menu.h"
#include "navbar.h"

#include <QInputDialog>
#include <QMainWindow>

class MainWindow : public QMainWindow, IDraw {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void Draw() override;

    void showBoards(const std::vector<Board> &boards) {
        boardManager.clear();

        // convert model data in ui data
        for (auto &board: boards) {
            BoardWidget *boardW = new BoardWidget(board.id, QString(board.name.data()));
            for (auto &column: board.columns) {
                ColumnWidget *columnW = new ColumnWidget(column.id, QString(column.name.data()));
                for (auto &card: column.cards) {
                    CardWidget *cardW = new CardWidget(card.id, column.id, QString(card.name.data()),
                                                       QString(card.caption.data()));
                    columnW->addCardWidget(cardW);
                }
                boardW->addColumnWidget(columnW);
            }
            boardW->Draw();
            boardManager.addBoardWidget(boardW);
        }

        // draw ui data
        QWidget *newWidget = nullptr;
        BoardWidget *boardW = boardManager.getBoardWidgets()[curBoardIndex];
        if (!boardManager.getBoardWidgets().empty()) {
            newWidget = boardW;
        } else {
            newWidget = new QLabel("No Boards :(");
        }

        QHBoxLayout *mainLayout = findChild<QHBoxLayout *>("mainLayout");
        mainLayout->removeWidget(curWidget);
//        delete curWidget;
        mainLayout->insertWidget(1, newWidget, Qt::AlignLeft);
        curWidget = newWidget;

        // connections
        QVector<QPushButton *> addCardLabels =
                findChildren<QPushButton *>("addCardButton");

        auto it = addCardLabels.begin();
        for (auto columnW: boardW->getColumnWidgets()) {
            connect(*it, &QPushButton::clicked,
                    [columnW, this] { onAddCardClicked(columnW->getID()); });
            ++it;
        }

        QPushButton *addColLabel = findChild<QPushButton *>("addColumnButton");
        connect(addColLabel, &QPushButton::clicked,
                [boardW, this] { onAddColumnClicked(boardW->getID()); });

        // For Navbar //
        QComboBox *chooseBoard = findChild<QComboBox *>("chooseBoard");
        chooseBoard->clear();
        for (auto bW: boardManager.getBoardWidgets()) {
            chooseBoard->addItem(QIcon("Gui/resources/background/default_board.jpg"),
                                 bW->GetText());
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
        std::cout << "boardManager.getBoardWidgets().size = " << boardManager.getBoardWidgets().size() << std::endl;
        BoardWidget *boardW = boardManager.getBoardWidgets()[index];
        std::cout << "replace: " << boardManager.getBoardWidgets()[curBoardIndex]->GetText().toStdString() << " " << curBoardIndex
                  << boardManager.getBoardWidgets()[index]->GetText().toStdString() << index;
        std::cout << "END"<< std::endl;
        QHBoxLayout *mainLayout = findChild<QHBoxLayout *>("mainLayout");
        mainLayout->removeWidget(curWidget);
//        delete curWidget;
        qInfo() << "AAAAA" << boardManager.getBoardWidgets()[index];
        mainLayout->insertWidget(1, boardManager.getBoardWidgets()[index], Qt::AlignLeft);
        std::cout << "END 2"<< std::endl;
        curWidget = boardW;
        resize();

        QVector<QPushButton *> addCardLabels =
                findChildren<QPushButton *>("addCardButton");

        // connections
        auto it = addCardLabels.begin();
        for (auto columnW: boardManager.getBoardWidgets()[index]->getColumnWidgets()) {
            connect(*it, &QPushButton::clicked,
                    [columnW, this] { onAddCardClicked(columnW->getID()); });
            ++it;
        }

        curBoardIndex = index;
        QPushButton *addColLabel = findChild<QPushButton *>("addColumnButton");
        connect(addColLabel, &QPushButton::clicked,
                [boardW, this] { onAddColumnClicked(boardW->getID()); });
    }

signals:

    void addObjectSignal(Object &, ObjType);

private:
    Navbar *navbar;
    Menu *menu;
    BoardWidgetManager boardManager;

    int curBoardIndex = 0;

    QWidget *curWidget = new QLabel("Load Boards.....");

    void resizeEvent(QResizeEvent *event) override;

    void resize();

    void setStyles();
};
