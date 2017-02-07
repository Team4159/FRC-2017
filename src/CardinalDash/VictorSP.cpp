#include "CardinalDash/VictorSP.h"

namespace CardinalDash
{
    VictorSP::VictorSP ( int port ) : frc::VictorSP ( port )
    {
        std::string name = "PWM/" + std::to_string ( port ) + " (VictorSP)";

        Dashboard::Subscribe ( name, &getValue, this );
    };

    double VictorSP::getValue ( void* instance )
    {
        return ( ( VictorSP* ) instance )->Get();
    }
}
