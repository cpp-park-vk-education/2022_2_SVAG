#include "CardDataBase.h"

#include <iostream>

CardDataBase::CardDataBase(std::shared_ptr<DataBase> cl) { client = cl; }

json CardDataBase::addCard(const json &info) const {
    json response = client->insert(info);
    return response;
}

json CardDataBase::removeCard(const size_t id) const {
    json response = client->remove({{"id", id}});
    return response;
}

json CardDataBase::updateCard(const json &info) const {
    json response = client->update(info);
    return response;
}

json CardDataBase::getCardInfo(const size_t id) const {
    json response = client->select({{"id", id}});
    return response;
}

json CardDataBase::getCardCheckLists(const size_t id) const {
    json response = client->select({{"id", id}});
    return response;
}

json CardDataBase::getCardTags(const size_t id) const {
    json response = client->select({{"id", id}});
    return response;
}

json CardDataBase::getCardColumn(const size_t id) const {
    json response = client->select({{"id", id}});
    return response;
}

json CardDataBase::addTag(const json &info) const {
    json response = client->insert(info);
    return response;
}

json CardDataBase::removeTag(const size_t id) const {
    json response = client->insert({{"id", id}});
    return response;
}

json CardDataBase::addCheckList(const json &info) const {
    json response = client->insert(info);
    return response;
}

json CardDataBase::removeCheckList(const size_t id) const {
    json response = client->insert({{"id", id}});
    return response;
}

json CardDataBase::addCheckListItem(const json &info) const {
    json response = client->insert(info);
    return response;
}

json CardDataBase::removeCheckListItem(const size_t id) const {
    json response = client->insert({{"id", id}});
    return response;
}
