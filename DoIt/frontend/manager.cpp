#include "manager.h"

Manager::Manager(QObject *parent) : QObject(parent) {
    connect(this, &Manager::sendBoardsSignal, &_guiWorker, &GuiWorker::sendBoardsSignal);
    connect(this, &Manager::sendColumnsSignal, &_guiWorker, &GuiWorker::sendColumnsSignal);
    connect(this, &Manager::sendCardsSignal, &_guiWorker, &GuiWorker::sendCardsSignal);

    // from gui worker
    connect(&_guiWorker, &GuiWorker::getColumnSignal, this, &Manager::getColumnsSlot);
    connect(&_guiWorker, &GuiWorker::getCardsSignal, this, &Manager::getCardsSlot);

    getBoards();
    getColumns();
    getCards();

    emit sendBoardsSignal(_boards);
}

Manager::~Manager() {
    _netWorker.disconnect();
}
