#pragma once

#include <QtWidgets>

#include "net_worker.h"
#include "gui_worker.h"

#include "qboard.h"
#include "quser.h"

#include "Lib/json.hpp"

using json = nlohmann::json;

class Manager : public QObject {
Q_OBJECT
public:
    explicit Manager(QObject *parent = nullptr);

    ~Manager() override;

    // get
    void getBoard() {
        qDebug() << "getBoard()";
        json data;
        data["cmd"] = "get board";
        std::string request = data.dump();

        int err = 0;
        _netWorker.sendMessage(request + '\n', err);
        std::string response = _netWorker.getMessage(err);
        std::cout << "Got response: " << response << std::endl;

        // parse response
        json resp = json::parse(response);
        _board.fromJson(resp["result"]);
    }

public slots:

    void addObjectSlot(Object &obj, ObjType objType) {
        qDebug() << "addObjectSlot()";
        json data = obj.toJson();
        data["cmd"] = "add " + _objType2Str(objType);

        std::string request = data.dump();

        int err = 0;
        _netWorker.sendMessage(request + '\n', err);
        if (err == 1) {
            return;
        } else {
            if (objType == BOARD) {
                _netWorker.sendFile(dynamic_cast<QBoard &>(obj).bgPath);
            }
        }
    }

    void deleteObjectSlot(size_t id, ObjType objType) {
        qDebug() << "deleteObjectSlot()";
        json data;
        data["cmd"] = "del " + _objType2Str(objType);
        data["id"] = id;
        std::string request = data.dump();

        int err = 0;
        _netWorker.sendMessage(request + '\n', err);
        if (err == 1) {
            // fail to connect
//            emit connectFailureSignal();
            return;
        } else {
//            emit connectSuccessSignal();
        }
    }

    void updateObjectSlot(Object &obj, ObjType objType) {
        qDebug() << "updateObjectSlot()";
        json data = obj.toJson();
        data["cmd"] = "update " + _objType2Str(objType);
        std::string request = data.dump();

        int err = 0;
        _netWorker.sendMessage(request + '\n', err);
        if (err == 1) {
            // fail to connect
//            emit connectFailureSignal();
            return;
        } else {
//            emit connectSuccessSignal();
        }
    }

    void authUserSlot(QUser &obj) {
        qDebug() << "authUserSlot()";
        json data = obj.toJson();
        data["cmd"] = "auth";
        std::string request = data.dump();

        int err = 0;
        _netWorker.sendMessage(request + '\n', err);
        if (err == 1) {
            // fail to connect
//            emit connectFailureSignal();
            return;
        } else {
//            emit connectSuccessSignal();
        }
    }

    void registerUserSlot(QUser &user) {
        qDebug() << "registerUserSlot()";
        json data = user.toJson();
        data["cmd"] = "register";
        std::string request = data.dump();

        int err = 0;
        _netWorker.sendMessage(request + '\n', err);
        if (err == 1) {
            // fail to connect
//            emit connectFailureSignal();
            return;
        } else {
//            emit connectSuccessSignal();
            if (!user.avatarPath.empty()) {
                _netWorker.sendFile(user.avatarPath);
            }
        }
    }

    void logoutSlot() {
        qDebug() << "logoutSlot()";
        json data;
        data["cmd"] = "logout";
        std::string request = data.dump();

        int err = 0;
        _netWorker.sendMessage(request + '\n', err);
        if (err == 1) {
            // fail to connect
//            emit connectFailureSignal();
            return;
        } else {
//            emit connectSuccessSignal();
        }
    }

    void addUserSlot(QUser &user, const size_t boardId) {
        qDebug() << "addUserSlot()";
        json data = user.toJson();
        data["cmd"] = "add user to board";
        data["board_id"] = boardId;
        std::string request = data.dump();

        int err = 0;
        _netWorker.sendMessage(request + '\n', err);
        if (err == 1) {
            // fail to connect
//            emit connectFailureSignal();
            return;
        } else {
//            emit connectSuccessSignal();
        }
    }

private:
    static std::string _objType2Str(ObjType objType) {
        switch (objType) {
            case BOARD:
                return "board";
            case COLUMN:
                return "column";
            case CARD:
                return "card";
            case TAG:
                return "tag";
            case CHECK_LIST:
                return "check_list";
            case CHECK_LIST_ITEM:
                return "check_list_item";
        }
        return "";
    }

private:
    NetWorker _netWorker;
    GuiWorker _guiWorker;

    size_t userId = 0;
    QBoard _board;
};
