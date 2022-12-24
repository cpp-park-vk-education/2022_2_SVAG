#include "card_widget.h"

CardWidget::CardWidget(QString _title, QString _caption)
    : title(_title), caption(_caption), tags(), history(QVector<Update>()),
      deadline(QDateTime()), comments(QVector<Comment>()) {}

CardWidget::CardWidget(QString _title, QString _caption, QVector<QString> _tags)
    : title(_title), caption(_caption), tags(_tags), history(QVector<Update>()),
      deadline(QDateTime()), comments(QVector<Comment>()) {}

CardWidget::CardWidget(QString _title, QString _caption, QDateTime _deadline)
    : title(_title), caption(_caption), tags(), history(QVector<Update>()),
      deadline(_deadline), comments(QVector<Comment>()) {}

CardWidget::CardWidget(QString _title, QString _caption, QVector<QString> _tags,
                       QDateTime _deadline)
    : title(_title), caption(_caption), tags(_tags), history(QVector<Update>()),
      deadline(_deadline), comments(QVector<Comment>()) {}

void CardWidget::SetText(const QString &_title) { title = _title; }

QString CardWidget::GetText() const { return title; }

void CardWidget::setCaption(const QString &_caption) { caption = _caption; }

QString CardWidget::getCaption() const { return caption; }

void CardWidget::addTags(QVector<QString> _tags) { tags.append(_tags); }

QVector<QString> CardWidget::getTags() const { return tags; }

void CardWidget::addToHistory(Update _update) { history.append(_update); }

QVector<Update> CardWidget::getHistory() const { return history; }

void CardWidget::setDeadline(const QDateTime &_deadline) {
  deadline = _deadline;
}

QDateTime CardWidget::getDeadline() const { return deadline; }

void CardWidget::addComment(Comment _comment) { comments.append(_comment); }

void CardWidget::deleteComment(Comment _comment) {
  comments.removeOne(_comment);
}

QVector<Comment> CardWidget::getComments() const { return comments; }

void CardWidget::setRowNum(const int &_rowNum) { rowNum = _rowNum; }

int CardWidget::getRowNum() const { return rowNum; }

bool operator==(const CardWidget &l, const CardWidget &r) {
  if (l.title == r.title && l.caption == r.caption && l.deadline == r.deadline)
    return true;

  return false;
}

QWidget *CardWidget::Draw() const {
  QTextEdit *textEdit = new QTextEdit(GetText());                // Data
  textEdit->setObjectName("textEdit");

  textEdit->setMinimumSize(QSize(200, 60));
  textEdit->setMaximumSize(QSize(230, 60));

  textEdit->setReadOnly(true);
  textEdit->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));

  return textEdit;
}
