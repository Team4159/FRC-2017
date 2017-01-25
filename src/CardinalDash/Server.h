#ifndef CARDINAL_DASH_SERVER_H
#define CARDINAL_DASH_SERVER_H

#include "easywsclient.hpp"

namespace CardinalDash {
    class Server {
    public:
        static void SendValues(std::string values);
    private:
        static constexpr const char* ipAddr = "ws://driverstation-4159.local:5800";
    };
};

#endif // CARDINAL_DASH_SERVER_H
