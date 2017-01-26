#ifndef CARDINAL_DASH_SERVER_H
#define CARDINAL_DASH_SERVER_H

#include <memory>

#include "easywsclient.hpp"
using easywsclient::WebSocket;

namespace CardinalDash {
    class Server {
    public:
        static void Init();
        static void SendValues(std::string values);
    private:
        static constexpr const char* ipAddr = "ws://drivestation-4159.local:5800";
        static WebSocket* webSocket;

        static bool connected;
    };
};

#endif // CARDINAL_DASH_SERVER_H
