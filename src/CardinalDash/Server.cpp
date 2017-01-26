#include "Server.h"

#include "easywsclient.hpp"
using easywsclient::WebSocket;

#include <memory>
#include <iostream>

namespace CardinalDash {
    WebSocket::pointer Server::webSocket;

    void Server::Init()
    {
        webSocket = WebSocket::from_url_no_mask(ipAddr);
        std::cout << webSocket << std::endl;
        std::cout << (webSocket == nullptr) << std::endl;
    }

    void Server::SendValues(std::string values)
    {
        webSocket->send(values);
        webSocket->poll();
    }
}
