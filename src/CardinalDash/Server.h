#ifndef CARDINAL_DASH_SERVER_H
#define CARDINAL_DASH_SERVER_H

#include <memory>

#include "easywsclient.hpp"
using easywsclient::WebSocket;

#include "json.hpp"
using json = nlohmann::json;

namespace CardinalDash {
    class Server {
    public:
        static void Init();
        static void SendValues(json values);
    private:
        static constexpr const char* ipAddr = "ws://Brandons-Mac.local:5800";
        static WebSocket* webSocket;

        static bool connected;
    };
};

#endif // CARDINAL_DASH_SERVER_H
