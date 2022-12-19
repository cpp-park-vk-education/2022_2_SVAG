#include "column_widget.h"

ColumnWidget::ColumnWidget(QString _name)
    : name(_name), cards(QVector<CardWidget>()) {}

ColumnWidget::ColumnWidget(QString _name, QVector<CardWidget> _cards)
    : name(_name), cards(_cards) {}

void ColumnWidget::SetText(const QString &_name) { name = _name; }

QString ColumnWidget::GetText() const { return name; }

void ColumnWidget::addCard(CardWidget _card) { cards.append(_card); }

void ColumnWidget::deleteCard(CardWidget _card) { cards.removeOne(_card); }

void ColumnWidget::swapCards(int first, int second) {
  cards.swapItemsAt(first, second);
}

QVector<CardWidget> ColumnWidget::getCards() { return cards; }

void ColumnWidget::setColNum(const int &_colNum) { colNum = _colNum; }

int ColumnWidget::getColNum() const { return colNum; }

int ColumnWidget::cardCount() const { return cards.size(); }

bool operator==(const ColumnWidget &l, const ColumnWidget &r) {
  if (l.name == r.name)
    return true;

  return false;
}

QWidget *ColumnWidget::Draw() const {
  // Column //
  QWidget *columnWidget = new QWidget();
  columnWidget->setObjectName("columnWidget");
  columnWidget->setContentsMargins(0, 0, 0, 0);

  QVBoxLayout *columnLayout = new QVBoxLayout(columnWidget);
  columnLayout->setObjectName("columnLayout");
  columnLayout->setContentsMargins(10, 5, 10, 10);

  // Column content //

  // Column title
  QHBoxLayout *columnTitleLayout = new QHBoxLayout();
  columnTitleLayout->setObjectName("columnTitleLayout");
  columnTitleLayout->setContentsMargins(0, 0, 0, 0);

  QLineEdit *columnTitle = new QLineEdit();
  columnTitle->setObjectName("columnTitle");
  columnTitle->setMinimumSize(QSize(150, 30));
  columnTitle->setMaximumSize(QSize(230, 30));
  columnTitle->setText(name); // Data
  columnTitle->setCursor(Qt::PointingHandCursor);

  QComboBox *moreActions = new QComboBox();
  moreActions->setObjectName("moreActions");
  moreActions->setFixedSize(QSize(20, 20));
  moreActions->setCursor(QCursor(Qt::PointingHandCursor));

  // Add title
  columnTitleLayout->addWidget(columnTitle);
  columnTitleLayout->addWidget(moreActions);

  // Scroll for cards
  QScrollArea *scrollAreaCards = new QScrollArea();
  scrollAreaCards->setObjectName("scrollAreaCards");
  scrollAreaCards->setMinimumSize(QSize(230, 0));
  scrollAreaCards->setContentsMargins(0, 0, 0, 0);
  scrollAreaCards->setWidgetResizable(true);
  scrollAreaCards->setFrameShape(QFrame::NoFrame);
  scrollAreaCards->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  QWidget *scrollAreaCardsContents = new QWidget(scrollAreaCards);
  scrollAreaCardsContents->setObjectName("scrollAreaCardsContents");
  scrollAreaCardsContents->setMinimumSize(QSize(230, 0));
  scrollAreaCardsContents->setContentsMargins(0, 0, 0, 0);

  // Cards in column
  QVBoxLayout *cardsLayout = new QVBoxLayout(scrollAreaCardsContents);
  cardsLayout->setObjectName("cardsLayout");
  cardsLayout->setContentsMargins(0, 0, 0, 0);
  cardsLayout->setSpacing(5);

  // Add cards //
  foreach (CardWidget card, cards) {
    QTextEdit *textEdit = qobject_cast<QTextEdit *>(card.Draw());

    cardsLayout->addWidget(textEdit);
    cardsLayout->setAlignment(textEdit, Qt::AlignHCenter);
  }

  scrollAreaCards->setWidget(scrollAreaCardsContents);
  scrollAreaCards->setFixedSize(scrollAreaCards->sizeHint());

  // Add card
  QWidget *addCardWidget = new QWidget();
  addCardWidget->setObjectName("addCardWidget");
  addCardWidget->setFixedSize(QSize(230, 30));
  addCardWidget->setCursor(QCursor(Qt::PointingHandCursor));
  addCardWidget->setContentsMargins(0, 0, 0, 0);

  QHBoxLayout *addCardLayout = new QHBoxLayout(addCardWidget);
  addCardLayout->setObjectName("addCardLayout");
  addCardLayout->setContentsMargins(0, 0, 0, 0);
  addCardLayout->setSpacing(0);

  // Add Card Content
  QLabel *plusIcon = new QLabel();
  plusIcon->setObjectName("plusIcon");
  plusIcon->setFixedSize(QSize(20, 20));
  plusIcon->setCursor(QCursor(Qt::PointingHandCursor));

  QLabel *addCardLabel = new QLabel(QObject::tr("Добавить карточку"));
  addCardLabel->setObjectName("addCardLabel");
  addCardLabel->setMinimumSize(QSize(100, 30));
  addCardLabel->setMaximumSize(QSize(200, 30));
  addCardLabel->setCursor(QCursor(Qt::PointingHandCursor));

  // Add content to layuot //
  addCardLayout->addWidget(plusIcon);
  addCardLayout->addWidget(addCardLabel);

  // Add content to layout //
  columnLayout->setAlignment(Qt::AlignTop);
  columnLayout->addLayout(columnTitleLayout);
  columnLayout->addWidget(scrollAreaCards);
  columnLayout->addWidget(addCardWidget);

  columnWidget->setFixedSize(250, columnLayout->sizeHint().height());

  columnWidget->setStyleSheet(
      QString::fromUtf8("#scrollAreaCards {\n"
                        "   background: transparent;\n"
                        "}\n"
                        "\n"
                        "#scrollAreaCardsContents {\n"
                        "   background: transparent;\n"
                        "}\n"
                        "\n"
                        "#columnWidget {\n"
                        "	background-color: rgb(243, 245, 250);\n"
                        "	border-radius: 10px;\n"
                        "}\n"
                        "\n"
                        "#columnWidget > QLineEdit {\n"
                        "	color: #172B4D;\n"
                        "   border-radius: 5px;\n"
                        "	background: transparent;\n"
                        "}\n"
                        "\n"
                        "#columnWidget > QLineEdit:focus {\n"
                        "	border: 1px solid blue;\n"
                        "	background-color: white;\n"
                        "}\n"
                        "\n"
                        "QTextEdit {\n"
                        "   border-radius: 8px;\n"
                        "	background-color: white;\n"
                        "}\n"
                        "\n"
                        "QTextEdit:hover {\n"
                        "	background-color: rgb(219, 220, 225);\n"
                        "}\n"
                        "\n"
                        "#moreActions {\n"
                        "   background: transparent;\n"
                        "	image: url(Gui/resources/icons/more.png);\n"
                        "}\n"
                        "\n"
                        "\n"
                        "#moreActions::drop-down {\n"
                        "	border: 0px;\n"
                        "}\n"
                        "\n"
                        "#moreActions QListView {\n"
                        "	min-width: 100px;\n"
                        "	background-color: white;\n"
                        "}\n"
                        "\n"
                        "#moreActions QListView::item {\n"
                        "    width: 100px;\n"
                        "    height: 30px;\n"
                        "}\n"
                        "\n"
                        "#moreActions QListView::item:focus, #moreActions "
                        "QListView::item:hover {\n"
                        "	color: black;\n"
                        "	background-color: silver;\n"
                        "}\n"
                        "\n"
                        "#plusIcon {\n"
                        "   image: url(Gui/resources/icons/plus_black.png);\n"
                        "}\n"
                        "\n"
                        "#addCardWidget:hover {\n"
                        "   background-color: rgb(215, 215, 215);\n"
                        "   color: #172B4D;"
                        "   border-radius: 5px;\n"
                        "}\n"
                        "\n"
                        ""));

  return columnWidget;
}
