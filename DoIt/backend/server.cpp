#include "server.h"

void TalkToClient::start() {
}

static ptr TalkToClient::new_() {

}

void TalkToClient::stop() {

}

bool TalkToClient::started() const {

}

ip::tcp::socket& TalkToClient::sock() {

}

std::string TalkToClient::username() const {

}

void TalkToClient::set_clients_changed() {

}

void  TalkToClient::on_read() {

}

void  TalkToClient::on_login() {

}

void TalkToClient::on_register() {

}

void TalkToClient::on_get_content() {

}

void TalkToClient::on_create_content() {

}

void TalkToClient::on_change_content() {

}

void TalkToClient::on_delete_content() {

}

void  TalkToClient::on_ping() {

}
void  TalkToClient::do_ping() {

}

void  TalkToClient::on_check_ping() {

}

void  TalkToClient::post_check_ping() {

}

void  TalkToClient::on_write() {

}

void  TalkToClient::do_read() {

}

void  TalkToClient::do_write() {

}

size_t  TalkToClient::read_complete() {
	return 0;
}

void Server::start_server() {

}

void Server::stop_server() {

}

void Server::handle_accept() {

}