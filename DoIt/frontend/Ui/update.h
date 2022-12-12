#pragma once

#include "user.h"
#include "main_interfaces.h"

class Update : public IDate {
public:
    Update() = default;
    Update(User _user, QDateTime _date);
    ~Update() = default;

    void setUser(const User& _user);
    User getUser() const;

    virtual void SetDate(QDateTime _date) override;
    virtual QDateTime GetDate() const override;

private:
    User user;
    // Action action;
    QDateTime date;
};
