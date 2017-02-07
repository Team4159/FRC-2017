#include "CardinalDash/Dashboard.h"

#include <json/json.hpp>
using json = nlohmann::json;

#include "Server.h"
#include "PDP.h"

namespace CardinalDash
{

    std::vector<Dashboard::DashboardValue>* Dashboard::subscribedValues = new std::vector<Dashboard::DashboardValue>();

    void Dashboard::Init()
    {
        Server::Init();
        PDP::Init();
    }

    void Dashboard::PushValues()
    {
        json data;

        for ( DashboardValue value : *subscribedValues ) {
            GetValue ( value, data );
        }

        Server::SendPeriodicData ( data );
    }

    void Dashboard::SubscribeToValue ( std::string name, Dashboard::DataType type, void* callback, void* object )
    {
        Dashboard::DashboardValue value = Dashboard::DashboardValue ( name, type, callback, object );
        subscribedValues->push_back ( value );
    }

    void Dashboard::GetValue ( DashboardValue value, json& data )
    {
        auto target = &data;

        std::vector<std::string> result = std::vector<std::string>();
        const char* str = value.name.c_str();

        do {
            const char* begin = str;
            while ( *str != '/' && *str ) {
                str++;
            }
            result.push_back ( std::string ( begin, str ) );
        } while ( 0 != *str++ );

        for ( auto i : result ) {
            target = & ( ( *target ) [i] );
        }

        if ( value.object == nullptr ) {
            switch ( value.type ) {
            case BOOL: {
                bool ( *callback ) () = ( bool ( * ) () ) value.callback;
                *target = callback();
            }
            break;
            case CHAR: {
                char ( *callback ) () = ( char ( * ) () ) value.callback;
                *target = callback();
            }
            break;
            case FLOAT: {
                float ( *callback ) () = ( float ( * ) () ) value.callback;
                *target = callback();
            }
            break;
            case DOUBLE: {
                double ( *callback ) () = ( double ( * ) () ) value.callback;
                *target = callback();
            }
            break;
            case INT: {
                int ( *callback ) () = ( int ( * ) () ) value.callback;
                *target = callback();
            }
            break;
            }
        } else {
            switch ( value.type ) {
            case BOOL: {
                bool ( *callback ) ( void* instance ) = ( bool ( * ) ( void* instance ) )
                                                        value.callback;
                *target = callback ( value.object );
            }
            break;
            case CHAR: {
                char ( *callback ) ( void* instance ) = ( char ( * ) ( void* instance ) )
                                                        value.callback;
                *target = callback ( value.object );
            }
            break;
            case FLOAT: {
                float ( *callback ) ( void* instance ) = ( float ( * ) ( void* instance ) )
                        value.callback;
                *target = callback ( value.object );
            }
            break;
            case DOUBLE: {
                double ( *callback ) ( void* instance ) = ( double ( * ) (
                            void* instance ) ) value.callback;
                *target = callback ( value.object );
            }
            break;
            case INT: {
                int ( *callback ) ( void* instance ) = ( int ( * ) ( void* instance ) )
                                                       value.callback;
                *target = callback ( value.object );
            }
            break;
            }
        }
    }

// It's pretty much the same thing for the rest of the file...

    void Dashboard::Subscribe ( std::string name, bool ( *callback ) () )
    {
        SubscribeToValue ( name, Dashboard::DataType::BOOL, ( void* ) callback, NULL );
    }

    void Dashboard::Subscribe ( std::string name, char ( *callback ) () )
    {
        SubscribeToValue ( name, Dashboard::DataType::CHAR, ( void* ) callback, NULL );
    }

    void Dashboard::Subscribe ( std::string name, float ( *callback ) () )
    {
        SubscribeToValue ( name, Dashboard::DataType::FLOAT, ( void* ) callback, NULL );
    }

    void Dashboard::Subscribe ( std::string name, double ( *callback ) () )
    {
        SubscribeToValue ( name, Dashboard::DataType::DOUBLE, ( void* ) callback, NULL );
    }

    void Dashboard::Subscribe ( std::string name, int ( *callback ) () )
    {
        SubscribeToValue ( name, Dashboard::DataType::INT, ( void* ) callback, NULL );
    }

// Nothing to see here...

    void Dashboard::Subscribe ( std::string name,
                                bool ( *callback ) ( void* instance ), void* object )
    {
        SubscribeToValue ( name, Dashboard::DataType::BOOL, ( void* ) callback, object );
    }

    void Dashboard::Subscribe ( std::string name,
                                char ( *callback ) ( void* instance ), void* object )
    {
        SubscribeToValue ( name, Dashboard::DataType::CHAR, ( void* ) callback, object );
    }

    void Dashboard::Subscribe ( std::string name,
                                float ( *callback ) ( void* instance ), void* object )
    {
        SubscribeToValue ( name, Dashboard::DataType::FLOAT, ( void* ) callback, object );
    }

    void Dashboard::Subscribe ( std::string name,
                                double ( *callback ) ( void* instance ), void* object )
    {
        SubscribeToValue ( name, Dashboard::DataType::DOUBLE, ( void* ) callback,
                           object );
    }

    void Dashboard::Subscribe ( std::string name,
                                int ( *callback ) ( void* instance ), void* object )
    {
        SubscribeToValue ( name, Dashboard::DataType::INT, ( void* ) callback, object );
    }

// Well aren't we nosy?
}
