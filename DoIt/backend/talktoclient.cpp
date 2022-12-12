#include "talktoclient.h"

void TalkToClient::start() 
{
    started_ = true;
    last_ping = boost::posix_time::microsec_clock::local_time();
    do_read();
}
void TalkToClient::stop() 
{
    if (!started_) return;
    started_ = false;
    sock_.close();
}
bool TalkToClient::started() const 
{ 
    return started_; 
}
boost::asio::ip::tcp::socket& TalkToClient::sock() 
{ 
    return sock_; 
}
std::string TalkToClient::username() const 
{ 
    return username_; 
}
void TalkToClient::on_read(const error_code& err, size_t bytes) {
    if (err) stop();
    if (!started()) return;
    std::string msg(read_buffer_, bytes);
    if (msg.find("login ") == 8) on_login(msg);
    else if (msg.find("ping") == 8) on_ping();
    else if (msg.find("get") == 8) on_get_content(msg);
    else on_invalid_msg(msg);
}
void TalkToClient::on_invalid_msg(const std::string& msg)
{
    json result;
    result["response"] = "invalid msg";
    std::string response = result.dump();
    response = response + '\n';
    do_write(response);
}
void TalkToClient::on_login(const std::string& msg) 
{
    std::istringstream in(msg);
    in >> username_ >> username_;
    std::cout << username_ << " logged in" << std::endl;
    json result;
    result["response"] = "login ok";
    std::string response = result.dump();
    response = response + '\n';
    do_write(response);
}
void TalkToClient::on_register() 
{
}

void TalkToClient::on_get_content(const std::string& msg) 
{
    json result = getBoardInfo(0);
    std::string response = result.dump();
    response = response + '\n';
    do_write(response);
}

void TalkToClient::on_create_content() 
{
}

void TalkToClient::on_change_content() 
{
}

void TalkToClient::on_delete_content() 
{
}

void TalkToClient::on_ping() 
{
    json result;
    result["response"] = "ping ok";
    std::string response = result.dump();
    response = response + '\n';
    do_write(response);
}

void TalkToClient::do_ping() {
        json result;
        result["response"] = "ping";
        std::string response = result.dump();
        response = response + '\n';
        do_write(response);
}

void TalkToClient::on_check_ping() 
{
    boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
    if ((now - last_ping).total_milliseconds() > 30000) {
        std::cout << "stopping " << username_ << " - no ping in time" << std::endl;
        stop();
    }
    last_ping = boost::posix_time::microsec_clock::local_time();
}
void TalkToClient::post_check_ping() {
    timer_.expires_from_now(boost::posix_time::millisec(30000));
    timer_.async_wait(MEM_FN(on_check_ping));
}

void TalkToClient::on_write(const error_code& err, size_t bytes) {
    do_read();
}

void TalkToClient::do_read() {
    async_read(sock_, boost::asio::buffer(read_buffer_), MEM_FN2(read_complete, _1, _2), MEM_FN2(on_read, _1, _2));
    post_check_ping();
}
void TalkToClient::do_write(const std::string& msg) {
    if (!started()) return;
    std::copy(msg.begin(), msg.end(), write_buffer_);
    sock_.async_write_some(boost::asio::buffer(write_buffer_, msg.size()),MEM_FN2(on_write, _1, _2));
}

size_t TalkToClient::read_complete(const boost::system::error_code& err, size_t bytes) {
    if (err) return 0;
    bool found = std::find(read_buffer_, read_buffer_ + bytes, '\n') < read_buffer_ + bytes;
    return found ? 0 : 1;
}