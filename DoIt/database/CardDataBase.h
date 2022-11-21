#pragma once

#include <string>

#include "PostgreDataBase.h"
#include "database.h"

class CardDataBase {
 public:
    CardDataBase() = default;
    CardDataBase(std::shared_ptr<DataBase> client);
    json addCard(const json &info) const;
    json removeCard(const int id) const;
    json updateCard(const json &info) const;
    json getCardInfo(const int id) const;
    json getCardCheckLists(const int id) const;
    json getCardTags(const int id) const;
    json getCardColumn(const int id) const;
    json addTag(const json &info) const;
    json removeTag(const int id) const;
    json addCheckList(const json &info) const;
    json removeCheckList(const int id) const;
    json addCheckListItem(const json &info) const;
    json removeCheckListItem(const int id) const;

 private:
    std::shared_ptr<DataBase> client;
};