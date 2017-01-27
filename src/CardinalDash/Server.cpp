#include "Server.h"

#include "easywsclient.hpp"
using easywsclient::WebSocket;

#include "json.hpp"
using json = nlohmann::json;

#include <memory>
#include <iostream>
#include <time.h>

namespace CardinalDash {
    WebSocket::pointer Server::webSocket;
    bool Server::connected = false;

    void Server::Init()
    {
        webSocket = WebSocket::from_url_no_mask(ipAddr);
        connected = (webSocket != nullptr);
    }

    void Server::SendValues(json values)
    {
        if(connected)
        {
            json data;
            time_t now = time(0);
            data[ctime(&now)] = values;
            webSocket->send(data.dump());
            webSocket->poll();
        } else {
            Init();
        }
    }
}
