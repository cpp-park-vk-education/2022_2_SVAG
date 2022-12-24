#include "main_manager.h"

MainManager::MainManager(QObject* parent)
    : QObject(parent), _netManager(), _guiManager(), _userManager(_netManager) {
    // connections
    connect(this, &MainManager::showBoardsSignal, this, &MainManager::showBoardsSlot);

    // from gui worker
    connect(&_guiManager, &GuiManager::authSignal, this, &MainManager::authSlot);
    connect(&_guiManager, &GuiManager::regSignal, this, &MainManager::regSlot);
    connect(&_guiManager, &GuiManager::addObjectSignal, this, &MainManager::addObjectSlot);

    // TODO: implement ping
    //    std::thread thr_ping([&]() { ping(); });
    //    thr_ping.detach();
}
