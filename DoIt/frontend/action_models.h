#pragma once

#include "user.h"

#include <string>

#include <QTime>

class Comment {
public:
    void SetDate(QTime time);
    QTime GetDate();
    void SetUser(User user);
    User GetUser();

private:
    std::string text;
    User user;
    QTime time;
};
