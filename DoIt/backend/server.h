#pragma once

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost::asio;
using namespace boost::posix_time;
using namespace std;

class TalkToClient : public boost::enable_shared_from_this<TalkToClient>
                     , boost::noncopyable {
    TalkToClient();
public:
    typedef boost::system::error_code error_code;
    typedef boost::shared_ptr<TalkToClient> ptr;

    void start();
    static ptr new_();
    void stop();
    bool started() const;
    ip::tcp::socket & sock();
    std::string username() const;
private:
    void on_read(); 
    void on_login();
    void on_register();
    void on_get_content();
    void on_create_content();
    void on_change_content();
    void on_delete_content();
    void on_ping();
    void do_ping();
    void on_check_ping();
    void post_check_ping();
    void on_write();
    void do_read();
    void do_write();
    size_t read_complete();

    ip::tcp::socket sock_;
    bool started_;
    std::string username_;
    deadline_timer timer_;
    boost::posix_time::ptime last_ping;
};

class Server {
public:
    void start_server();
    void stop_server();
    void handle_accept();
private:
    io_service service;
    ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8001));
    typedef boost::shared_ptr<TalkToClient> client_ptr;
    typedef std::vector<client_ptr> Array;
    Array clients;
    bool status;
};