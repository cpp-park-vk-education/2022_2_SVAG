#pragma once

#include <QDebug>

#include "card_widget.h"

class ColumnWidget : public IText, IDraw {
public:
  ColumnWidget(QString _name);
  ColumnWidget(QString _name, QVector<CardWidget> _cards);
    ~ColumnWidget() = default;

    virtual void SetText(const QString& _name) override;
    virtual QString GetText() const override;

    void addCard(CardWidget _card);
    void deleteCard(CardWidget _card);
    void swapCards(int first, int second);
    QVector<CardWidget> getCards();

    void setColNum(const int& _colNum);
    int getColNum() const;

    int cardCount() const;


    friend bool operator==(const ColumnWidget& l, const ColumnWidget& r);

    QWidget* Draw() const override;

private:
    QString name;
    QVector<CardWidget> cards;

    int colNum;
};
