#pragma once

#include "user.h"
#include "main_interfaces.h"


class Comment : public IText, IDate {
public:
    Comment() = default;
    Comment(QString _text, User _user, QDateTime _date);
    ~Comment() = default;

    void setUser(const User& _user);
    User getUser() const;

    virtual void SetText(const QString& _text) override;
    virtual QString GetText() const override;

    virtual void SetDate(QDateTime _date) override;
    virtual QDateTime GetDate() const override;


    friend bool operator==(const Comment& l, const Comment& r);

private:
    QString text;
    User user;
    QDateTime date;
};
