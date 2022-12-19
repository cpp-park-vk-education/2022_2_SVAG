#include "board_widget.h"

#include <iostream>

BoardWidget::BoardWidget(QString _name)
    : name(_name), columns(QVector<ColumnWidget>()), users(QVector<UiUser>()),
      history(QVector<Update>()) {}

BoardWidget::BoardWidget(QString _name, QVector<ColumnWidget> _columns)
    : name(_name), columns(_columns), users(QVector<UiUser>()),
      history(QVector<Update>()) {}

BoardWidget::BoardWidget(QString _name, QVector<ColumnWidget> _columns,
                         QVector<UiUser> _users)
    : name(_name), columns(_columns), users(_users),
      history(QVector<Update>()) {}

void BoardWidget::SetText(const QString &_name) { name = _name; }

QString BoardWidget::GetText() const { return name; }

void BoardWidget::addColumn(ColumnWidget _column) { columns.append(_column); }

void BoardWidget::deleteColumn(ColumnWidget _column) {
  columns.removeOne(_column);
}

void BoardWidget::swapColumns(int first, int second) {
  columns.swapItemsAt(first, second);
}

QVector<ColumnWidget> BoardWidget::getColumns() { return columns; }

void BoardWidget::setUsers(QVector<UiUser> _users) { users.append(_users); }

QVector<UiUser> BoardWidget::getUsers() const { return users; }

void BoardWidget::addToHistory(Update _update) { history.append(_update); }

QVector<Update> BoardWidget::getHistory() const { return history; }

int BoardWidget::getID() const { return ID; }

int BoardWidget::columnCount() const { return columns.size(); }

bool operator==(const BoardWidget &l, const BoardWidget &r) {
  if (l.GetText() == r.GetText())
    return true;

  return false;
}

QWidget *BoardWidget::Draw() const {
  // Board //
  QWidget *boardWidget = new QWidget();
  boardWidget->setObjectName("boardWidget");
  boardWidget->setMinimumSize(QSize(600, 500));
  boardWidget->setContentsMargins(0, 0, 0, 0);

  QVBoxLayout *boardLayout = new QVBoxLayout(boardWidget);
  boardLayout->setObjectName("boardLayout");
  boardLayout->setContentsMargins(0, 0, 0, 0);
  boardLayout->setSpacing(0);

  // Board Header //
  QWidget *headerBoardWidget = new QWidget();
  headerBoardWidget->setObjectName("headerBoardWidget");
  headerBoardWidget->setMinimumSize(QSize(600, 40));
  headerBoardWidget->setMaximumSize(QSize(2000, 40));
  headerBoardWidget->setContentsMargins(0, 0, 0, 0);

  QHBoxLayout *headerBoardLayout = new QHBoxLayout(headerBoardWidget);
  headerBoardLayout->setObjectName("headerBoardLayout");
  headerBoardLayout->setContentsMargins(10, 0, 10, 0);

  // Board content //
  QLabel *currentBoardName = new QLabel(name);
  currentBoardName->setObjectName("currentBoardName");
  currentBoardName->setMinimumSize(QSize(150, 30));
  currentBoardName->setMaximumSize(QSize(300, 30));

  QSpacerItem *bwSpacer =
      new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

  // Add
  headerBoardLayout->addWidget(currentBoardName);
  headerBoardLayout->addItem(bwSpacer);

  QHBoxLayout *usersLayout = new QHBoxLayout();
  usersLayout->setObjectName("usersLayout");
  usersLayout->setContentsMargins(0, 0, 0, 0);

  // Board user icons
  for (int i = 0; i < 4; ++i) {
    QLabel *userIcon = new QLabel();
    userIcon->setObjectName("userIcon");
    userIcon->setMinimumSize(QSize(30, 30));
    userIcon->setMaximumSize(QSize(30, 30));
    userIcon->setCursor(QCursor(Qt::PointingHandCursor));
    userIcon->setStyleSheet("image: url(Gui/resources/icons/default_user.png)");

    usersLayout->addWidget(userIcon);
  }

  // Button to add users to board
  QPushButton *addUsers = new QPushButton(QObject::tr("Добавить"));
  addUsers->setObjectName("addUsers");
  addUsers->setMinimumSize(QSize(150, 30));
  addUsers->setMaximumSize(QSize(200, 30));
  addUsers->setCursor(QCursor(Qt::PointingHandCursor));
  addUsers->setIcon(QIcon("Gui/resources/icons/add_user.png"));

  // Add //
  headerBoardLayout->addLayout(usersLayout);
  headerBoardLayout->addWidget(addUsers);

  boardLayout->addWidget(headerBoardWidget);

  // Main Board //
  QWidget *mainBoardWidget = new QWidget();
  mainBoardWidget->setObjectName("mainBoardWidget");
  mainBoardWidget->setMinimumSize(QSize(600, 500));
  mainBoardWidget->setContentsMargins(0, 0, 0, 0);

  // Scroll for columns
  QScrollArea *scrollAreaBoard = new QScrollArea(mainBoardWidget);
  scrollAreaBoard->setObjectName("scrollAreaBoard");
  scrollAreaBoard->setContentsMargins(0, 0, 0, 0);
  scrollAreaBoard->setWidgetResizable(true);
  scrollAreaBoard->setFrameShape(QFrame::NoFrame);
  scrollAreaBoard->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  QWidget *scrollAreaBoardContents = new QWidget(scrollAreaBoard);
  scrollAreaBoardContents->setObjectName("scrollAreaBoardContents");
  scrollAreaBoardContents->setContentsMargins(0, 0, 0, 0);

  // Layout in scroll
  QHBoxLayout *mainBoardLayout = new QHBoxLayout(scrollAreaBoardContents);
  mainBoardLayout->setObjectName("mainBoardLayout");
  mainBoardLayout->setContentsMargins(10, 0, 10, 0);
  mainBoardLayout->setSpacing(10);
  mainBoardLayout->setAlignment(Qt::AlignLeft);

  // Draw columns
  foreach (ColumnWidget column, columns) {
    QWidget *columnWidget = column.Draw();

    mainBoardLayout->addWidget(columnWidget);
    mainBoardLayout->setAlignment(columnWidget, Qt::AlignTop);
  }

  // Draw extra column
  QWidget *addColumnWidget = new QWidget();
  addColumnWidget->setObjectName("addColumnWidget");
  addColumnWidget->setFixedSize(QSize(250, 40));
  addColumnWidget->setCursor(QCursor(Qt::PointingHandCursor));
  addColumnWidget->setContentsMargins(0, 0, 0, 0);

  QHBoxLayout *addColumnLayout = new QHBoxLayout(addColumnWidget);
  addColumnLayout->setObjectName("addColumnLayout");
  addColumnLayout->setContentsMargins(0, 0, 0, 0);
  addColumnLayout->setSpacing(0);

  // Add Card Content
  QLabel *plusIcon = new QLabel();
  plusIcon->setObjectName("plusIcon");
  plusIcon->setFixedSize(QSize(20, 20));
  plusIcon->setCursor(QCursor(Qt::PointingHandCursor));

  QLabel *addColumnLabel = new QLabel(QObject::tr("Добавить ещё одну колонку"));
  addColumnLabel->setObjectName("addColumnLabel");
  addColumnLabel->setMinimumSize(QSize(100, 40));
  addColumnLabel->setMaximumSize(QSize(200, 40));
  addColumnLabel->setCursor(QCursor(Qt::PointingHandCursor));

  // Add content to layout //
  addColumnLayout->addWidget(plusIcon);
  addColumnLayout->addWidget(addColumnLabel);

  // Add extra column to layout //
  mainBoardLayout->addWidget(addColumnWidget);
  mainBoardLayout->setAlignment(addColumnWidget, Qt::AlignTop);

  scrollAreaBoard->setWidget(scrollAreaBoardContents);

  boardLayout->addWidget(mainBoardWidget);

  boardWidget->setStyleSheet(QString::fromUtf8(
      "#boardWidget {\n"
      "	border-image: url(Gui/resources/background/default_board.jpg) 0 0 0 0 "
      "stretch stretch;\n"
      "}\n"
      "\n"
      "#headerBoardLayout {\n"
      "	background: transparent;\n"
      "}\n"
      "\n"
      "#headerBoardWidget > * {\n"
      "	color: white;\n"
      "}\n"
      "\n"
      "#currentBoardName {\n"
      "	font: bold 20px;\n"
      "}\n"
      "\n"
      "#addUsers {\n"
      "	color: black;\n"
      "	background-color: white;\n"
      "	border-radius: 5px;\n"
      "	border: 1px solid silver;\n"
      "}\n"
      "\n"
      "#addUsers:hover {\n"
      "	color: black;\n"
      "	background-color: silver;\n"
      "}\n"
      "\n"
      "#mainBoardWidget {\n"
      "	background: transparent;\n"
      "}\n"
      "\n"
      "#scrollAreaBoard {\n"
      "	background: transparent;\n"
      "}\n"
      "\n"
      "#scrollAreaBoardContents {\n"
      "	background: transparent;\n"
      "}\n"
      "#plusIcon {\n"
      "   image: url(Gui/resources/icons/plus_white.png);\n"
      "}\n"
      "\n"
      "#addColumnWidget {\n"
      "   background-color: rgba(120, 120, 120, 90);\n"
      "   border-radius: 5px;\n"
      "}\n"
      "\n"
      "#addColumnWidget:hover {\n"
      "   background-color: rgba(120, 120, 120, 60);\n"
      "}\n"
      "\n"
      "#addColumnLabel {\n"
      "   color: #ffffff;\n"
      "}\n"
      ""));

  return boardWidget;
}

BoardManager::BoardManager(QVector<BoardWidget> _boards) : boards(_boards) {}

void BoardManager::addBoard(BoardWidget _board) { boards.append(_board); }

void BoardManager::deleteBoard(BoardWidget _board) { boards.removeOne(_board); }

QVector<BoardWidget> BoardManager::getBoards() { return boards; }

BoardWidget BoardManager::getBoard(int _boardNum) {
  //    foreach (BoardWidget board, boards) {
  //        if (board.getBoardNum() == _boardNum)
  //            return board;
  //    }

  //    return BoardWidget("");
}

BoardWidget BoardManager::first() const { return boards.first(); }

bool BoardManager::empty() const { return boards.empty(); }
