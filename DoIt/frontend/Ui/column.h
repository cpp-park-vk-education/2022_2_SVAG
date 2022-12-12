#pragma once

#include "card.h"


class Column : public IText, IDraw {
public:
    Column() = default;
    Column(QString _name);
    Column(QString _name, QVector<Card> _cards);
    ~Column() = default;

    virtual void SetText(const QString& _name) override;
    virtual QString GetText() const override;

    void addCard(Card _card);
    void deleteCard(Card _card);
    void swapCards(int first, int second);
    QVector<Card> getCards();

    void setColNum(const int& _colNum);
    int getColNum() const;

    int cardCount() const;


    friend bool operator==(const Column& l, const Column& r);

    virtual QWidget* Draw() const override;

private:
    QString name;
    QVector<Card> cards;

    int colNum;
};
