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
    explicit Manager(QObject *parent = nullptr) : QObject(parent) {
        // connect from gui worker
        // object
        connect(&_guiWorker, &GuiWorker::addObjectSignal, this, &Manager::addObjectSlot);
        connect(&_guiWorker, &GuiWorker::delObjectSignal, this, &Manager::deleteObjectSlot);
        connect(&_guiWorker, &GuiWorker::updateObjectSignal, this, &Manager::updateObjectSlot);

        // user
        connect(&_guiWorker, &GuiWorker::authUserSignal, this, &Manager::authUserSlot);
        connect(&_guiWorker, &GuiWorker::registerUserSignal, this, &Manager::registerUserSlot);
        connect(&_guiWorker, &GuiWorker::logoutSignal, this, &Manager::logoutSlot);
        connect(&_guiWorker, &GuiWorker::addUserSignal, this, &Manager::addUserSlot);
    }

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
