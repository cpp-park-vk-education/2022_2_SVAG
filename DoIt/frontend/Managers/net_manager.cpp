#include "net_manager.h"

void NetManager::pingLoop() {
  try {
    _ping_sock.connect(_ep);
  } catch (boost::system::system_error &err) {
    std::cout << "Ping Connect failed\n";
    return;
  }
  while (started_) {
    json js_ping;
    int err = 0;
    js_ping["cmd"] = "ping";
    asio::write(_ping_sock, asio::buffer(js_ping.dump() + "\n"),
                asio::transfer_all());
    size_t bytes = boost::asio::read(
        _ping_sock, asio::buffer(_buff_ping),
        boost::bind(&NetManager::read_complete, _buff_ping, _1, _2));
    std::string response(_buff_ping, bytes - 1); // -1 to remove \n

    json resp = json::parse(response);

    boost::this_thread::sleep(boost::posix_time::millisec(3000));
  }

  _ping_sock.close();
}

void NetManager::connect() {
  try {
    _sock.connect(_ep);
  } catch (boost::system::system_error &err) {
    std::cout << "Connect failed\n";
    throw err;
  }
}
