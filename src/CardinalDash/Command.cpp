#include "CardinalDash/Command.h"

#include "CardinalDash/Server.h"

#include <iostream>

#include <json/json.hpp>
using json = nlohmann::json;

namespace CardinalDash
{

    Command::Command ( const std::string& name ) : frc::Command ( name )
    {
        std::string prefix = "Commands/" + std::to_string ( GetID() ) + " (" + name + ")";

        Dashboard::Subscribe ( prefix + "/running", &GetRunning, this );
        Dashboard::Subscribe ( prefix + "/phase", &GetPhase, this );

        phase = 0;
    };

    Command::Command() : Command ( "no name" )
    {
    };

    int Command::GetPhase()
    {
        return phase;
    }

    bool Command::GetRunning ( void* instance )
    {
        return ( ( Command* ) instance )->IsRunning();
    }

    int Command::GetPhase ( void* instance )
    {
        return ( ( Command* ) instance )->GetPhase();
    }

    void Command::SetPhase ( int newPhase )
    {
        phase = newPhase;
    }

    void Command::Event ( std::string message )
    {
        json data;

        data["sender"] = std::to_string ( GetID() ) + " (" + GetName() + ")";

        data["message"] = message;

        Server::SendEventData(data);
    }
}
