#pragma once

#include <QtWidgets>

#include "net_worker.h"
#include "gui_worker.h"

#include "Lib/json.hpp"
#include "object.h"
#include "user.h"
#include "board.h"

using json = nlohmann::json;

class Manager : public QObject {
Q_OBJECT
public:
    explicit Manager(QObject *parent = nullptr);

    ~Manager() override = default;

    // get
    void getBoards() {
    }

    void getUser() {
    }

public slots:

    // запросы на сервер
    // добавить объект типа objType
    void addObjectSlot(Object &obj, ObjType objType) {
    }

    // удалить объект с id типа objType
    void deleteObjectSlot(size_t id, ObjType objType) {
    }

    // обновить объект типа objType
    void updateObjectSlot(Object &obj, ObjType objType) {
    }

    void authUserSlot(User &obj) {
    }

    void registerUserSlot(User &user) {
    }

    void logoutSlot() {
    }

    // добавить другого пользователя на доску
    void addUserSlot(User &user, const size_t boardId) {
    }

private:
    NetWorker _netWorker;
    GuiWorker _guiWorker;

    size_t userId = 0;
    std::vector<Board> _boards;
};
