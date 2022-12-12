#pragma once

#include "talktoclient.h"

class Server : public boost::enable_shared_from_this<Server>, boost::noncopyable {
public:
    typedef Server self_type;
    typedef boost::shared_ptr<Server> ptr;
    Server() : acceptor(service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8001)), status(false)
    {}
    static ptr new_() {
        ptr new_(new Server);
        return new_;
    }
    static ptr start()
    {
        ptr new_(new Server());
        new_->start_server();
        return new_;
    }
    void start_server();
    void stop_server();
    void handle_accept(TalkToClient::ptr client, const boost::system::error_code& err);
private:
    boost::asio::ip::tcp::acceptor acceptor;
    bool status;
};