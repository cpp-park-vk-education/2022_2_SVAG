#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <iostream>
#include "json.hpp"
#include "database_interaction.h"
using json = nlohmann::json;
boost::asio::io_service service;

#define MEM_FN(x)       boost::bind(&self_type::x, shared_from_this())
#define MEM_FN1(x,y)    boost::bind(&self_type::x, shared_from_this(),y)
#define MEM_FN2(x,y,z)  boost::bind(&self_type::x, shared_from_this(),y,z)


class TalkToClient : public boost::enable_shared_from_this<TalkToClient>, boost::noncopyable {
    typedef TalkToClient self_type;
    TalkToClient() : sock_(service), started_(false), timer_(service), clients_changed_(false) {}
public:
    typedef boost::system::error_code error_code;
    typedef boost::shared_ptr<TalkToClient> ptr;

    static ptr new_() {
        ptr new_(new TalkToClient);
        return new_;
    }
    void start();
    void stop();
    bool started() const;
    boost::asio::ip::tcp::socket& sock();
    std::string username() const;
private:
    void on_read(const error_code& err, size_t bytes);
    void on_login(const std::string& msg);
    void on_ping();
    void do_ping();
    void on_check_ping();
    void post_check_ping();
    void on_work_with_database(json msg_json);
    void on_write(const error_code& err, size_t bytes);
    void do_read();
    void do_write(const std::string& msg);
    size_t read_complete(const boost::system::error_code& err, size_t bytes);
private:
    boost::asio::ip::tcp::socket sock_;
    enum { max_msg = 1024 };
    char read_buffer_[max_msg];
    char write_buffer_[max_msg];
    bool started_;
    std::string username_;
    boost::asio::deadline_timer timer_;
    boost::posix_time::ptime last_ping;
    bool clients_changed_;
    DatabaseInteraction interactor;
    json_to_string_response_convert convert;
};