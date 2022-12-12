#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <iostream>
#include "json.hpp"
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
    void on_read(const error_code& err, size_t bytes) {
        if (err) stop();
        if (!started()) return;
        std::string msg(read_buffer_, bytes);
        //std::cout << msg << std::endl;
        if (msg.find("login ") == 8) on_login(msg);
        else if (msg.find("ping") == 8) on_ping();
        else if (msg.find("get") == 8) on_get_content(msg);
        else on_invalid_msg(msg);
    }
    void on_invalid_msg(const std::string& msg)
    {
        json result;
        result["response"] = "invalid msg";
        std::string response = result.dump();
        response = response + '\n';
        do_write(response);
    }
    void on_login(const std::string& msg) {
        std::istringstream in(msg);
        in >> username_ >> username_;
        std::cout << username_ << " logged in" << std::endl;
        json result;
        result["response"] = "login ok";
        std::string response = result.dump();
        response = response + '\n';
        do_write(response);
    }
    void on_register() {
    }

    void on_get_content(const std::string& msg) {
       json result = getBoardInfo(0);
       std::string response = result.dump();
       response = response + '\n';
       do_write(response);
    }

    void on_create_content() {
    }

    void on_change_content() {
    }

    void on_delete_content() {
    }

    void on_ping() {
        json result;
        result["response"] = "ping ok";
        std::string response = result.dump();
        response = response + '\n';
        do_write(response);
    }

    void do_ping() {
        json result;
        result["response"] = "ping";
        std::string response = result.dump();
        response = response + '\n';
        do_write(response);
    }

    void on_check_ping() {
        boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
        if ((now - last_ping).total_milliseconds() > 30000) {
            std::cout << "stopping " << username_ << " - no ping in time" << std::endl;
            stop();
        }
        last_ping = boost::posix_time::microsec_clock::local_time();
    }
    void post_check_ping() {
        timer_.expires_from_now(boost::posix_time::millisec(30000));
        timer_.async_wait(MEM_FN(on_check_ping));
    }


    void on_write(const error_code& err, size_t bytes) {
        do_read();
    }
    void do_read() {
        async_read(sock_, boost::asio::buffer(read_buffer_), MEM_FN2(read_complete, _1, _2), MEM_FN2(on_read, _1, _2));
        post_check_ping();
    }
    void do_write(const std::string& msg) {
        if (!started()) return;
        std::copy(msg.begin(), msg.end(), write_buffer_);
        sock_.async_write_some(boost::asio::buffer(write_buffer_, msg.size()),MEM_FN2(on_write, _1, _2));
    }
    size_t read_complete(const boost::system::error_code& err, size_t bytes) {
        if (err) return 0;
        bool found = std::find(read_buffer_, read_buffer_ + bytes, '\n') < read_buffer_ + bytes;
        // we read one-by-one until we get to enter, no buffering
        return found ? 0 : 1;
    }
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
};