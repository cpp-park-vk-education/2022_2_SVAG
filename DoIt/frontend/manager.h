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
    void getBoards() {
        json data;
        data["cmd"] = "get boards";
        std::string request = data.dump();

        int err = 0;
        _netWorker.sendMessage(request + "\n", err);
        std::string response = _netWorker.getMessage(err);

        json resp = json::parse(response);

        QBoard board;
        for (auto jsBoard: resp["result"]) {
            board.fromJson(jsBoard);
            _boards.push_back(board);
        }
    }

    void getColumns() {
        json data;
        data["cmd"] = "get columns";
        for (auto &board: _boards) {
            data["board_id"] = board.id;
            std::string request = data.dump();
            int err = 0;
            _netWorker.sendMessage(request + "\n", err);
            std::string response = _netWorker.getMessage(err);
            json resp = json::parse(response);

            QColumn col;
            for (auto jsCol: resp["result"]) {
                col.fromJson(jsCol);
                board.columns.push_back(col);
            }
        }
    }

    // using net worker
    void getCards() {
        json data;
        data["cmd"] = "get cards";
        for (auto &board: _boards) {
            for (auto &column: board.columns) {
                data["board_id"] = board.id;
                data["column_id"] = column.id;
                std::string request = data.dump();
                int err = 0;
                _netWorker.sendMessage(request + "\n", err);
                std::string response = _netWorker.getMessage(err);
                json resp = json::parse(response);

                QCard card;
                for (auto jsCard: resp["result"][0]["cards"]) {
                    card.fromJson(jsCard);
                    column.cards.push_back(card);
                }
            }
        }
    }

public slots:

    // from gui worker
    void getColumnsSlot(size_t id) {
        for (auto board: _boards) {
            if (board.id == id) {
                emit sendColumnsSignal(board.columns);
            }
        }
    }

    void getCardsSlot(size_t id) {
        for (auto &board: _boards) {
            for (auto &column: board.columns) {
                if (column.id == id) {
                    emit sendCardsSignal(column.cards);
                }
            }
        }
    }

    void addObjectSlot(Object &obj, ObjType objType) {
        json data = obj.toJson();
        data["cmd"] = "add " + _objType2Str(objType);
        data["user_id"] = _userId;

        // from db module
        std::string request = data.dump();
        int err = 0;
        _netWorker.sendMessage(request + '\n', err);

        std::string response = _netWorker.getMessage(err);

        json test_res = json::parse(
                "{\"result\":[{\"background\":\"\",\"caption\":\"bbbbbbbb\",\"id\":4,\"name\":\"aaaaaa\"}],\"status\":\"ok\"}");
//        json resp = json::parse(response);
        obj.id = test_res["result"][0]["id"]; // set id for new object
        if (objType == BOARD) {
            _boards.push_back(dynamic_cast<QBoard &>(obj));
            emit sendBoardsSignal(_boards);
        } else if (objType == COLUMN) {
            _boards[data["board_id"]].columns.push_back(dynamic_cast<QColumn &>(obj));
            emit sendColumnsSignal(_boards[data["board_id"]].columns);
        }
    }

    void deleteObjectSlot(size_t id, ObjType objType) {
        json data;
        data["cmd"] = "del " + _objType2Str(objType);
        data["id"] = id;
        std::string request = data.dump();

        int err = 0;
        _netWorker.sendMessage(request + '\n', err);
        if (objType == BOARD) {
            for (auto it = _boards.begin(); it != _boards.end(); ++it) {
                if ((*it).id == id) {
                    _boards.erase(it);
                    break;
                }
            }
            emit sendBoardsSignal(_boards);
        } else if (objType == COLUMN) {
        }
    }

    void updateObjectSlot(Object &obj, ObjType objType) {
        json data = obj.toJson();
        data["cmd"] = "update " + _objType2Str(objType);
        std::string request = data.dump();

        int err = 0;
        _netWorker.sendMessage(request + '\n', err);
    }

    void authUserSlot(QUser &obj) {
        json data = obj.toJson();
        data["cmd"] = "auth";
        std::string request = data.dump();

        int err = 0;
        _netWorker.sendMessage(request + '\n', err);
    }

    void registerUserSlot(QUser &user) {
        json data = user.toJson();
        data["cmd"] = "register";
        std::string request = data.dump();

        int err = 0;
        _netWorker.sendMessage(request + '\n', err);
    }

    void logoutSlot() {
        json data;
        data["cmd"] = "logout";
        std::string request = data.dump();

        int err = 0;
        _netWorker.sendMessage(request + '\n', err);
    }

    void addUserSlot(QUser &user, const size_t boardId) {
        json data = user.toJson();
        data["cmd"] = "add user to board";
        data["board_id"] = boardId;
        std::string request = data.dump();

        int err = 0;
        _netWorker.sendMessage(request + '\n', err);
    }

signals:

    void sendBoardsSignal(std::vector<QBoard> &boards);

    void sendColumnsSignal(std::vector<QColumn> &columns);

    void sendCardsSignal(std::vector<QCard> &cards);

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

    size_t _userId = 0;
    std::vector<QBoard> _boards;
};
