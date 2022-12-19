#pragma once

#include "update.h"
#include "comment.h"

class CardWidget : public IText, IDraw {
public:
  CardWidget(QString _title, QString _caption);
  CardWidget(QString _title, QString _caption, QVector<QString> _tags);
  CardWidget(QString _title, QString _caption, QDateTime _deadline);
  CardWidget(QString _title, QString _caption, QVector<QString> _tags, QDateTime _deadline);
    ~CardWidget() = default;

    virtual void SetText(const QString& _title) override;
    virtual QString GetText() const override;

    void setCaption(const QString& _caption);
    QString getCaption() const;

    void addTags(QVector<QString> _tags);
    QVector<QString> getTags() const;

    void addToHistory(Update _update);
    QVector<Update> getHistory() const;

    void setDeadline(const QDateTime& _deadline);
    QDateTime getDeadline() const;

    void addComment(Comment _comment);
    void deleteComment(Comment _comment);
    QVector<Comment> getComments() const;

    void setRowNum(const int& _rowNum);
    int getRowNum() const;


    friend bool operator==(const CardWidget& l, const CardWidget& r);

    QWidget* Draw() const override;

private:
    QString title;
    QString caption;
    QVector<QString> tags;
    QVector<Update> history;
    QDateTime deadline;
    QVector<Comment> comments;

    int rowNum;
};
