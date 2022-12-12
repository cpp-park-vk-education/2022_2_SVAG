#include "user.h"


User::User(QString _name) : name(_name) {

}


User::User(const User& other) {
    name = other.name;
}


User& User::operator=(const User& other) {
    if (this != &other) {
        this->~User();
        new (this) User(other.name);
    }

    return *this;
}


void User::setName(const QString& _name) {
    name = _name;
}


QString User::getName() const {
    return name;
}


bool operator==(const User& l, const User& r) {
    if (l.name == r.name)
        return true;

    return false;
}
