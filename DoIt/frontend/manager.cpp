#include "manager.h"

Manager::Manager(QObject *parent) : QObject(parent) {
    try {
        _netWorker.connect();
//        _netWorker.loop();
    } catch (boost::system::system_error &err) {
        std::cout << "client terminated: " << err.what() << std::endl;
    }
}

Manager::~Manager() {
    _netWorker.disconnect();
}
