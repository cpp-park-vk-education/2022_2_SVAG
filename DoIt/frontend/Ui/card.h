#pragma once

#include "update.h"
#include "comment.h"

#include <QVector>

class Card : public IText, IDraw {
public:
    Card() = default;
    Card(QString _title, QString _caption);
    Card(QString _title, QString _caption, QVector<QString> _tags);
    Card(QString _title, QString _caption, QDateTime _deadline);
    Card(QString _title, QString _caption, QVector<QString> _tags, QDateTime _deadline);
    ~Card() = default;

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


    friend bool operator==(const Card& l, const Card& r);

    virtual QWidget* Draw() const override;

private:
    QString title;
    QString caption;
    QVector<QString> tags;
    QVector<Update> history;
    QDateTime deadline;
    QVector<Comment> comments;

    int rowNum;
};
