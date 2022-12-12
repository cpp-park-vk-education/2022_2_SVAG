#include "card.h"


Card::Card(QString _title, QString _caption) :
    title(_title),
    caption(_caption),
    tags(0),
    history(0),
    deadline(QDateTime()),
    comments(0)
{
}


Card::Card(QString _title, QString _caption, QVector<QString> _tags) :
    title(_title),
    caption(_caption),
    tags(_tags),
    history(0),
    deadline(QDateTime()),
    comments(0)
{

}


Card::Card(QString _title, QString _caption, QDateTime _deadline):
    title(_title),
    caption(_caption),
    tags(0),
    history(0),
    deadline(_deadline),
    comments(0)
{

}


Card::Card(QString _title, QString _caption, QVector<QString> _tags, QDateTime _deadline) :
    title(_title),
    caption(_caption),
    tags(_tags),
    history(0),
    deadline(_deadline),
    comments(0)
{

}


void Card::SetText(const QString& _title) {
    title = _title;
}


QString Card::GetText() const {
    return title;
}


void Card::setCaption(const QString& _caption) {
    caption = _caption;
}


QString Card::getCaption() const {
    return caption;
}


void Card::addTags(QVector<QString> _tags) {
    tags.append(_tags);
}


QVector<QString> Card::getTags() const {
    return tags;
}


void Card::addToHistory(Update _update) {
    history.append(_update);
}


QVector<Update> Card::getHistory() const {
    return history;
}


void Card::setDeadline(const QDateTime& _deadline) {
    deadline = _deadline;
}


QDateTime Card::getDeadline() const {
    return deadline;
}


void Card::addComment(Comment _comment) {
    comments.append(_comment);
}


void Card::deleteComment(Comment _comment) {
    comments.removeOne(_comment);
}


QVector<Comment> Card::getComments() const {
    return comments;
}


void Card::setRowNum(const int& _rowNum) {
    rowNum = _rowNum;
}


int Card::getRowNum() const {
    return rowNum;
}


bool operator==(const Card& l, const Card& r) {
    if (l.title == r.title && l.caption == r.caption && l.deadline == r.deadline)
        return true;

    return false;
}


QWidget* Card::Draw() const {
    QTextEdit* textEdit = new QTextEdit();

    textEdit->setText(title);
    textEdit->setReadOnly(true);
    textEdit->setMaximumSize(QSize(16777215, 80));

    return textEdit;
}
