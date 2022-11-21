#pragma once

#include <QString>
#include <ctime>

#include "json.hpp"

namespace Data {

using json = nlohmann::json;

struct ISerializable {
  virtual ~ISerializable() = 0;

  virtual json toJson() = 0;
};

struct UserCredentials : public ISerializable {
  std::string username;
  std::string password;

  UserCredentials() = default;
  UserCredentials(const std::string &_username, const std::string &_password)
      : username(_username), password(_password) {
  }

  json toJson() override {
    return json();
  }
};

struct CheckListItem : public ISerializable {
  int id;
  std::string title;
  int checkListId;

  json toJson() override {
    return json();
  }
};

struct CheckList : public ISerializable {
  int id;
  std::string title;
  std::vector<CheckListItem> items;
  int cardId;

  json toJson() override {
    return json();
  }
};

struct Tag : public ISerializable {
  int id;
  std::string name;
  std::string color;
  int cardId;

  json toJson() override {
    return json();
  }
};

struct Card : public ISerializable {
  int id;
  std::string title;
  std::string description;
  tm *deadline;
  std::vector<Tag> tags;
  std::vector<CheckList> checkLists;
  int columnId;

  json toJson() override {
    return json();
  }
};

struct Column : public ISerializable {
  int id;
  std::string name;
  std::vector<Card> cards;
  int deskId;

  json toJson() override {
    return json();
  }
};

struct Desk : public ISerializable {
  int id;
  std::string name;
  std::string bgPath;
  std::vector<Column> columns;

  json toJson() override {
    return json();
  }
};

struct User : public ISerializable {
  std::string username;
  std::string password;
  std::string email;
  std::string avatarPath;

  json toJson() override {
    return json();
  }
};

}  // namespace Data