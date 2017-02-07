#include "PDP.h"

#include "WPILib.h"

namespace CardinalDash
{
    std::unique_ptr<PowerDistributionPanel> PDP::pdp =
        std::make_unique<PowerDistributionPanel>();

    void PDP::Init()
    {
        Dashboard::Subscribe ( "PDP/Voltage", &GetVoltage );

        // Goodbye any chance of a programming internship...
        Dashboard::Subscribe ( "PDP/Current/0", &GetChannelCurrent0 );
        Dashboard::Subscribe ( "PDP/Current/1", &GetChannelCurrent1 );
        Dashboard::Subscribe ( "PDP/Current/2", &GetChannelCurrent2 );
        Dashboard::Subscribe ( "PDP/Current/3", &GetChannelCurrent3 );

        Dashboard::Subscribe ( "PDP/Current/4", &GetChannelCurrent4 );
        Dashboard::Subscribe ( "PDP/Current/5", &GetChannelCurrent5 );
        Dashboard::Subscribe ( "PDP/Current/6", &GetChannelCurrent6 );
        Dashboard::Subscribe ( "PDP/Current/7", &GetChannelCurrent7 );

        Dashboard::Subscribe ( "PDP/Current/8", &GetChannelCurrent8 );
        Dashboard::Subscribe ( "PDP/Current/9", &GetChannelCurrent9 );
        Dashboard::Subscribe ( "PDP/Current/10", &GetChannelCurrent10 );
        Dashboard::Subscribe ( "PDP/Current/11", &GetChannelCurrent11 );

        Dashboard::Subscribe ( "PDP/Current/12", &GetChannelCurrent12 );
        Dashboard::Subscribe ( "PDP/Current/13", &GetChannelCurrent13 );
        Dashboard::Subscribe ( "PDP/Current/14", &GetChannelCurrent14 );
        Dashboard::Subscribe ( "PDP/Current/15", &GetChannelCurrent15 );
    }

    double PDP::GetVoltage()
    {
        return pdp->GetVoltage();
    }

    double PDP::GetChannelCurrent ( int channel )
    {
        return pdp->GetCurrent ( channel );
    }
}
