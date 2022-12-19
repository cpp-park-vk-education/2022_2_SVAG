#pragma once

#include <QtWidgets>

#include <iostream>
#include <thread>

#include "gui_manager.h"
#include "net_manager.h"
#include "user_manager.h"

#include "board.h"
#include "user.h"

#include "Lib/json.hpp"

using json = nlohmann::json;

class MainManager : public QObject {
    Q_OBJECT
  public:
    MainManager(QObject* parent = nullptr)
        : QObject(parent), _netManager(), _guiManager(), _userManager(_netManager) {

        connect(this, &MainManager::showBoardsSignal, this, &MainManager::showBoardsSlot);

        //     from gui worker
        connect(&_guiManager, &GuiManager::authSignal, this, &MainManager::authSlot);
        connect(&_guiManager, &GuiManager::regSignal, this, &MainManager::regSlot);

        //    std::thread thr_ping([&]() { ping(); });
        //    thr_ping.detach();
    }

    ~MainManager() override = default;

    void ping() {
        try {
            _netManager.pingLoop();
        } catch (boost::system::system_error& err) { std::cout << "Failed to do ping\n"; }
    }

    void getAllUserData() {
        getUserBoards();
        getColumns();
        getCards();

        showBoardsSignal();
    }

    // get
    void getUserBoards() {
        json data;
        data["cmd"] = "get boards";
        data["user_id"] = 1;
        std::string request = data.dump();

        int err = 0;
        _netManager.connect();
        _netManager.sendMessage(request + "\n", err);
        std::string response = _netManager.getMessage(err);
        _netManager.disconnect();

        json resp = json::parse(response);

        Board board;
        for (auto jsBoard : resp["result"]) {
            jsBoard["id"] = jsBoard["board_id"];
            jsBoard["board_id"] = nullptr;
            board.fromJson(jsBoard);
            _boards.push_back(board);
        }
    }

    void getColumns() {
        json data;
        data["cmd"] = "get columns";
        for (auto& board : _boards) {
            data["board_id"] = board.id;
            std::string request = data.dump();
            int err = 0;
            _netManager.connect();
            _netManager.sendMessage(request + "\n", err);
            std::string response = _netManager.getMessage(err);
            json resp = json::parse(response);
            _netManager.disconnect();

            Column col;
            for (auto jsCol : resp["result"]) {
                col.fromJson(jsCol);
                board.columns.push_back(col);
            }
        }
    }

    // using net worker
    void getCards() {
        json data;
        data["cmd"] = "get cards";
        for (auto& board : _boards) {
            for (auto& column : board.columns) {
                data["board_id"] = board.id;
                data["column_id"] = column.id;
                std::string request = data.dump();
                int err = 0;
                _netManager.connect();
                _netManager.sendMessage(request + "\n", err);
                std::string response = _netManager.getMessage(err);
                json resp = json::parse(response);
                _netManager.disconnect();

                Card card;
                for (auto jsCard : resp["result"][0]["cards"]) {
                    card.fromJson(jsCard);
                    column.cards.push_back(card);
                }
            }
        }
    }

  public slots:
    void authSlot(const User& user) {
        _userManager.authUser(user);
    }

    void regSlot(const User& user) {
        _userManager.regUser(user);

        _guiManager.showLoadAllData();

        std::thread thr_first_get_boards([&]() { getAllUserData(); });
        thr_first_get_boards.detach();
    }

    void showBoardsSlot() {
        _guiManager.showBoards(_boards);
    };

    void addObjectSlot(Object& obj, ObjType objType) {
        json data = obj.toJson();
        data["cmd"] = "add " + _objType2Str(objType);
        data["user_id"] = _userManager.userId();

        // from db module
        std::string request = data.dump();
        int err = 0;
        _netManager.sendMessage(request + '\n', err);

        std::string response = _netManager.getMessage(err);

        json test_res = json::parse("{\"result\":[{\"background\":\"\",\"caption\":\"bbbbbbbb\",\"id\":4,"
                                    "\"name\":\"aaaaaa\"}],\"status\":\"ok\"}");
        //        json resp = json::parse(response);
        obj.id = test_res["result"][0]["id"];  // set id for new object
        if (objType == BOARD) {
            _boards.push_back(dynamic_cast<Board&>(obj));
            emit sendBoardsSignal(_boards);
        } else if (objType == COLUMN) {
            _boards[data["board_id"]].columns.push_back(dynamic_cast<Column&>(obj));
            emit sendColumnsSignal(_boards[data["board_id"]].columns);
        }
    }

    void deleteObjectSlot(size_t id, ObjType objType) {
        json data;
        data["cmd"] = "del " + _objType2Str(objType);
        data["id"] = id;
        std::string request = data.dump();

        int err = 0;
        _netManager.sendMessage(request + '\n', err);
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

    void updateObjectSlot(Object& obj, ObjType objType) {
        json data = obj.toJson();
        data["cmd"] = "update " + _objType2Str(objType);
        std::string request = data.dump();

        int err = 0;
        _netManager.sendMessage(request + '\n', err);
    }

    void logoutSlot() {
        json data;
        data["cmd"] = "logout";
        std::string request = data.dump();

        int err = 0;
        _netManager.sendMessage(request + '\n', err);
    }

  signals:

    void showBoardsSignal();

    void sendBoardsSignal(std::vector<Board>& boards);

    void sendColumnsSignal(std::vector<Column>& columns);

    void sendCardsSignal(std::vector<Card>& cards);

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
    NetManager _netManager;
    GuiManager _guiManager;
    UserManager _userManager;

    std::vector<Board> _boards;
};
