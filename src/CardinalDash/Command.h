#ifndef CARDINAL_DASH_COMMAND_H
#define CARDINAL_DASH_COMMAND_H

#include <Commands/Command.h>

#include "CardinalDash/Dashboard.h"

namespace CardinalDash
{

    class Command : public frc::Command
    {
        public:
            Command ( const std::string& name );
            Command();

            int GetPhase();

            static bool GetRunning ( void* instance );
            static int GetPhase ( void* instance );
        private:
            int phase;

            void SetPhase ( int newPhase );
            void Event ( std::string message );
    };

};

#endif // CARDINAL_DASH_COMMAND_H
