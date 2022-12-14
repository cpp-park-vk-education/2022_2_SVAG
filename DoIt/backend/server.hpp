#pragma once

#include "talktoclient.hpp"

class Server : public boost::enable_shared_from_this<Server>, boost::noncopyable {
public:
    typedef Server self_type;
    typedef boost::shared_ptr<Server> ptr;
    Server() : acceptor(service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), status(false)
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
    void start_server()
    {
        TalkToClient::ptr client = TalkToClient::new_();
        acceptor.async_accept(client->sock(), boost::bind(&Server::handle_accept, shared_from_this(), client, _1));
        service.run();
        status = true;
    }
    void stop_server()
    {
        service.stop();
        status = false;
    }
    void handle_accept(TalkToClient::ptr client, const boost::system::error_code& err) 
    {
        client->start();
        TalkToClient::ptr new_client = TalkToClient::new_();
        acceptor.async_accept(new_client->sock(), boost::bind(&Server::handle_accept, shared_from_this(), new_client, _1));
    }
private:
    const int port = 8001;
    boost::asio::ip::tcp::acceptor acceptor;
    bool status;
};