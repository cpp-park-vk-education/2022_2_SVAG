#include "column.h"


Column::Column(QString _name) : name(_name), cards(0) {

}


Column::Column(QString _name, QVector<Card> _cards) : name(_name), cards(_cards) {

}


void Column::SetText(const QString& _name) {
    name = _name;
}


QString Column::GetText() const {
    return name;
}


void Column::addCard(Card _card) {
    cards.append(_card);
}


void Column::deleteCard(Card _card) {
    cards.removeOne(_card);
}


void Column::swapCards(int first, int second) {
    qSwap(cards.begin()[first], cards.begin()[second]);
}


QVector<Card> Column::getCards() {
    return cards;
}


void Column::setColNum(const int& _colNum) {
    colNum = _colNum;
}


int Column::getColNum() const {
    return colNum;
}


int Column::cardCount() const {
    return cards.size();
}


bool operator==(const Column& l, const Column& r) {
    if (l.name == r.name)
        return true;

    return false;
}


QWidget* Column::Draw() const {
    QWidget *widget = new QWidget();
    widget->setMaximumWidth(300);
    widget->setMinimumWidth(300);

    QVBoxLayout* layout = new QVBoxLayout(widget);

    QLineEdit *lineEdit = new QLineEdit(name);
    lineEdit->setMinimumSize(QSize(0, 30));

    layout->addWidget(lineEdit);

    for (int i = 0; i < cards.size(); ++i)
        layout->addWidget(qobject_cast<QTextEdit*>(cards[i].Draw()));

    QSpacerItem *spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addItem(spacerItem);

    return widget;
}
