#include "manager.h"

Manager::Manager(QObject *parent) : QObject(parent) {
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