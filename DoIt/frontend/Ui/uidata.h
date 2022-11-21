#pragma once

#include <QString>

namespace UiData {

struct Login {
  QString username;
  QString password;
};

struct Register {
  QString username;
  QString password;
};

struct CheckListItem {
  int id;
  QString title;
  int checkListId;
};

struct CheckList {
  int id;
  QString title;
  std::vector<CheckListItem> items;
  int cardId;
};

struct Tag {
  int id;
  QString name;
  QString color;
  int cardId;
};

struct Card {
  int id;
  QString title;
  QString description;
  tm deadline;
  std::vector<Tag> tags;
  std::vector<CheckList> checkLists;
  int columnId;
};

struct Column {
  int id;
  QString name;
  std::vector<Card> cards;
  int deskId;
};

struct Desk {
  int id;
  QString name;
  QString bgPath;
  std::vector<Column> columns;
};

struct User {
  QString username;
  QString password;
  QString email;
  QString avatarPath;
};

}  // namespace UiData