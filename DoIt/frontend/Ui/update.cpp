#include "update.h"


Update::Update(User _user, QDateTime _date) : user(_user), date(_date) {

}


void Update::setUser(const User& _user) {
    user = _user;
}


User Update::getUser() const {
    return user;
}


void Update::SetDate(QDateTime _date) {
    date = _date;
}


QDateTime Update::GetDate() const {
    return date;
}
