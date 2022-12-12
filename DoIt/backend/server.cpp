#include "server.h"

void Server::start_server()
{
    TalkToClient::ptr client = TalkToClient::new_();
    acceptor.async_accept(client->sock(), boost::bind(&Server::handle_accept, shared_from_this(), client, _1));
    service.run();
    status = true;
}
void Server::stop_server()
{
    service.stop();
    status = false;
}
void Server::handle_accept(TalkToClient::ptr client, const boost::system::error_code& err) 
{
    client->start();
    TalkToClient::ptr new_client = TalkToClient::new_();
    acceptor.async_accept(new_client->sock(), boost::bind(&Server::handle_accept, shared_from_this(), new_client, _1));
}