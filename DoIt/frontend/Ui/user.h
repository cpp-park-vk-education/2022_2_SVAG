#pragma once

#include <QString>


class User {
public:
    User() = default;
    User(QString _name);
    ~User() = default;

    User(const User& other);
    User& operator=(const User& other);

    void setName(const QString& _name);
    QString getName() const;


    friend bool operator==(const User& l, const User& r);

private:
    QString name;
    // image
};
