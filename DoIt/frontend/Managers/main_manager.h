#pragma once

#include <QtWidgets>

#include "client.h"
#include "data.h"
#include "json.hpp"
#include "uidata.h"
#include "uimanager.h"

using json = nlohmann::json;

class MainManager : public QObject {
  Q_OBJECT
 public:
  MainManager();

  ~MainManager() override;

  // post sign in
  void loginUser(const UiData::Login &login) {
    Data::UserCredentials uc(
        login.username.toStdString(),
        login.password.toStdString());  // convert ui data to data
    json body = uc.toJson();
    Request request;
    request.body = body.dump();
    // fill request ...
    netClient->sendRequest(request);
  }
  void registerUser(const UiData::Register &) {
  }

  // post new
  void newDesk(const UiData::Desk &uiDesk) {
  }
  void newColumn(const UiData::Column &) {
  }
  void newCard(const UiData::Card &) {
  }
  void newTag(const UiData::Tag &) {
  }
  void newCheckList(const UiData::CheckList &) {
  }
  void newCheckListItem(const UiData::CheckListItem &) {
  }

  // post change
  void changeDesk(const UiData::Desk &) {
  }
  void changeColumn(const UiData::Column &) {
  }
  void changeCard(const UiData::Card &) {
  }
  void changeTag(const UiData::Tag &) {
  }
  void changeCheckList(const UiData::CheckList &) {
  }
  void changeCheckListItem(const UiData::CheckListItem &) {
  }

  // post del
  void delDesk(const UiData::Desk &) {
  }
  void delColumn(const UiData::Column &) {
  }
  void delCard(const UiData::Card &) {
  }
  void delTag(const UiData::Tag &) {
  }
  void delCheckList(const UiData::CheckList &) {
  }
  void delCheckListItem(const UiData::CheckListItem &) {
  }

  // get
  void getDesks() {
  }
  void getUser() {
  }

 private:
  NetClient *netClient;
  UiManager uiManager;
  size_t userId = 0;
  std::vector<Data::Desk> desks;
};
