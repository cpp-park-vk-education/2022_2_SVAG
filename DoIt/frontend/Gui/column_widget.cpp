#include "column_widget.h"


ColumnWidget::ColumnWidget(size_t _ID) :
        ID(_ID),
        name(""),
        cardWidgets(QVector<CardWidget *>()) {

}


ColumnWidget::ColumnWidget(size_t _ID, QString _name) :
        ID(_ID),
        name(""),
        cardWidgets(QVector<CardWidget *>()) {

}


ColumnWidget::ColumnWidget(size_t _ID, QString _name, QVector<CardWidget *> _cardWidgets) :
        ID(_ID),
        name(_name),
        cardWidgets(_cardWidgets) {

}


void ColumnWidget::SetText(const QString &_name) {
    name = _name;
}


QString ColumnWidget::GetText() const {
    return name;
}


void ColumnWidget::addCardWidget(CardWidget *_cardWidget) {
    cardWidgets.append(_cardWidget);
}


void ColumnWidget::deleteCardWidget(CardWidget *_cardWidget) {
    cardWidgets.removeOne(_cardWidget);
}


void ColumnWidget::swapCardWidgets(const int &first, const int &second) {
    cardWidgets.swapItemsAt(first, second);
}


QVector<CardWidget *> ColumnWidget::getCardWidgets() {
    return cardWidgets;
}


CardWidget *ColumnWidget::getCardWidget(size_t _ID) {
    foreach(CardWidget * cardWidget, cardWidgets)
    {
        if (cardWidget->getID() == _ID)
            return cardWidget;
    }

    return nullptr;
}


size_t ColumnWidget::getID() const {
    return ID;
}


size_t ColumnWidget::cardsCount() const {
    return cardWidgets.size();
}


bool operator==(const ColumnWidget &l, const ColumnWidget &r) {
    if (l.name == r.name)
        return true;

    return false;
}


void ColumnWidget::Draw() {
    // Column //
    // setAttribute()
    setObjectName("columnWidget");
    setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *columnLayout = new QVBoxLayout(this);
    columnLayout->setObjectName("columnLayout");
    columnLayout->setContentsMargins(10, 10, 10, 10);

    // Column content //

    // Column title
    QHBoxLayout *columnTitleLayout = new QHBoxLayout();
    columnTitleLayout->setObjectName("columnTitleLayout");
    columnTitleLayout->setContentsMargins(0, 0, 0, 0);

    QLineEdit *columnTitle = new QLineEdit();
    columnTitle->setObjectName("columnTitle");
    columnTitle->setFixedSize(QSize(elementsWidth, titleHeight));
    columnTitle->setText(name);                                // Data
    columnTitle->setCursor(Qt::PointingHandCursor);

    QComboBox *moreActions = new QComboBox();
    moreActions->setObjectName("moreActions");
    moreActions->setFixedSize(QSize(smallIconSize, smallIconSize));
    moreActions->setCursor(QCursor(Qt::PointingHandCursor));


    // moreActions->addItems();

    // Add title
    columnTitleLayout->addWidget(columnTitle);
    columnTitleLayout->addWidget(moreActions);


    // Scroll for cards
    QScrollArea *scrollAreaCards = new QScrollArea();
    scrollAreaCards->setObjectName("scrollAreaCards");
    scrollAreaCards->setMinimumSize(QSize(elementsWidth, 0));
    scrollAreaCards->setContentsMargins(0, 0, 0, 0);
    scrollAreaCards->setWidgetResizable(true);
    scrollAreaCards->setFrameShape(QFrame::NoFrame);
    scrollAreaCards->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QWidget *scrollAreaCardsContents = new QWidget(scrollAreaCards);
    scrollAreaCardsContents->setObjectName("scrollAreaCardsContents");
    scrollAreaCardsContents->setMinimumSize(QSize(elementsWidth, 0));
    scrollAreaCardsContents->setContentsMargins(0, 0, 0, 0);


    // Cards in column
    QVBoxLayout *cardsLayout = new QVBoxLayout(scrollAreaCardsContents);
    cardsLayout->setObjectName("cardsLayout");
    cardsLayout->setContentsMargins(0, 0, 0, 0);
    cardsLayout->setSpacing(5);


    // Add cards //
    foreach(CardWidget * cardWidget, cardWidgets)
    {
        cardWidget->Draw();

        cardsLayout->addWidget(cardWidget);
        cardsLayout->setAlignment(cardWidget, Qt::AlignHCenter | Qt::AlignTop);
    }

    scrollAreaCards->setWidget(scrollAreaCardsContents);
    scrollAreaCards->setFixedSize(scrollAreaCards->sizeHint());


    // Add card
    QPushButton *addCardButton = new QPushButton(QObject::tr("Добавить карточку"));
    addCardButton->setObjectName("addCardButton");
    addCardButton->setFixedSize(QSize(elementsWidth, itemHeight));
    addCardButton->setIcon(QIcon("Gui/resources/icons/plus_black.png"));


    // Add content to layout //
    columnLayout->setAlignment(Qt::AlignTop);
    columnLayout->addLayout(columnTitleLayout);
    columnLayout->addWidget(scrollAreaCards);
    columnLayout->addWidget(addCardButton);


    setFixedSize(Width, columnLayout->sizeHint().height());

    // Styles
    setStyles();
}


void ColumnWidget::mouseReleaseEvent(QMouseEvent *event) {
    qInfo() << "Clicked on column with ID" << getID();
}


void ColumnWidget::setStyles() {
    setStyleSheet
            (
                    QString::fromUtf8
                            (
                                    "#scrollAreaCards {\n"
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
                                    "   padding-left: 5px;\n"
                                    "}\n"
                                    "\n"
                                    "#columnWidget > QLineEdit:focus {\n"
                                    "	border: 1px solid blue;\n"
                                    "	background-color: white;\n"
                                    "}\n"
                                    "\n"
                                    "#moreActions {\n"
                                    "   background: transparent;\n"
                                    "	image: url(Gui/resources/icons/more.png);\n"
                                    "}\n"
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
                                    "#moreActions QListView::item:focus, #moreActions QListView::item:hover {\n"
                                    "	color: black;\n"
                                    "	background-color: silver;\n"
                                    "}\n"
                                    "\n"
                                    "#addCardButton {\n"
                                    "   background-color: transparent;\n"
                                    "   border: 0px;\n"
                                    "   border-radius: 5px;\n"
                                    "   text-align: left;\n"
                                    "   padding-left: 5px;\n"
                                    "}\n"
                                    "\n"
                                    "#addCardButton:hover {\n"
                                    "   background-color: rgb(215, 215, 215);\n"
                                    "   color: #172B4D;"
                                    "   border-radius: 5px;\n"
                                    "}\n"
                                    "\n"
                                    ""
                            )
            );
}
