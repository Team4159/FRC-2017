#ifndef CARDINAL_DASH_SERVER_H
#define CARDINAL_DASH_SERVER_H

#include <memory>
#include <set>

#define ASIO_STANDALONE

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
typedef websocketpp::connection_hdl connection;

typedef websocketpp::server<websocketpp::config::asio> server;

#include <json/json.hpp>
using json = nlohmann::json;

namespace CardinalDash
{
    class Server
    {
        public:
            static void Init();
            static void SendPeriodicData ( json data );
            static void SendEventData ( json data );
            static void OnOpen ( connection con );
            static void OnClose ( connection con );
            static void Term();
        private:
            static const int SERVER_PORT = 5800;

            static server m_server;

            static void RunServer();

            static std::set<connection,std::owner_less<connection>> clients;
            static std::thread server_thread;
    };
};

#endif // CARDINAL_DASH_SERVER_H
