#include "Server.h"

#include "easywsclient.hpp"
using easywsclient::WebSocket;

#include <memory>
#include <iostream>

namespace CardinalDash {
    void Server::SendValues(std::string values)
    {
        std::unique_ptr<WebSocket> ws(WebSocket::from_url(ipAddr));
        ws->send(values);
        while (ws->getReadyState() != WebSocket::CLOSED) {
            WebSocket::pointer wsp = &*ws; // <-- because a unique_ptr cannot be copied into a lambda
            ws->poll();
            ws->dispatch([wsp](const std::string & message) {
                std::cout << message << std::endl;
                wsp->close();
            });
        }
    }
}
