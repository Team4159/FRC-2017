#include "Server.h"

#define ASIO_STANDALONE

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::bind;

#include <memory>
#include <iostream>
#include <chrono>
#include <string>

namespace CardinalDash
{
    server Server::m_server;
    std::set<connection,std::owner_less<connection>> Server::clients;
    std::thread Server::server_thread;

    void Server::Init()
    {
        clients = std::set<connection,std::owner_less<connection>>();

        try {
            m_server.init_asio();
        } catch ( const std::exception& e ) {
            std::cout << e.what();
        }

        // Disable all console spam from server
        m_server.clear_access_channels ( websocketpp::log::alevel::all );

        try {
            m_server.set_open_handler ( bind ( &Server::OnOpen,_1 ) );
            m_server.set_close_handler ( bind ( &Server::OnClose,_1 ) );
        } catch ( const std::exception& e ) {
            std::cout << e.what();
        }

        try {
            server_thread = std::thread ( Server::RunServer );
        } catch ( const std::exception& e ) {
            std::cout << e.what();
        }
    }

    void Server::SendPeriodicData ( json data )
    {
        json sendData;
        std::chrono::milliseconds ms =
            std::chrono::duration_cast< std::chrono::milliseconds > (
                std::chrono::system_clock::now().time_since_epoch()
            );
        sendData["time"] = std::to_string ( ms.count() );
        sendData["type"] = "periodic";
        sendData["data"] = data;
        std::set<connection,std::owner_less<connection>>::iterator it;
        for ( it = clients.begin(); it != clients.end(); ++it ) {
            m_server.send ( *it,sendData.dump(),websocketpp::frame::opcode::text );
        }
    }

    void Server::SendEventData ( json data )
    {
        json sendData;
        std::chrono::milliseconds ms =
            std::chrono::duration_cast< std::chrono::milliseconds > (
                std::chrono::system_clock::now().time_since_epoch()
            );
        sendData["time"] = std::to_string ( ms.count() );
        sendData["type"] = "event";
        sendData["data"] = data;
        std::set<connection,std::owner_less<connection>>::iterator it;
        for ( it = clients.begin(); it != clients.end(); ++it ) {
            m_server.send ( *it,sendData.dump(),websocketpp::frame::opcode::text );
        }
    }

    void Server::Term()
    {
        m_server.stop_listening();
    }

    void Server::OnOpen ( connection hdl )
    {
        clients.insert ( hdl );
    }

    void Server::OnClose ( connection hdl )
    {
        clients.erase ( hdl );
    }

    void Server::RunServer()
    {
        m_server.listen ( 5800 );
        m_server.start_accept();
        m_server.run();
    }
}
