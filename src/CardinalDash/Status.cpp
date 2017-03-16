#include "Status.h"

#include "Dashboard.h"
#include "WPILib.h"

namespace CardinalDash
{
    void Status::Init()
    {
        Dashboard::Subscribe ( "RoboRIO/Enabled", &GetEnabled );
        Dashboard::Subscribe ( "RoboRIO/Mode", &GetMode );
        Dashboard::Subscribe ( "RoboRIO/Alliance", &GetAlliance );
    }

    bool Status::GetEnabled()
    {
        return frc::DriverStation::GetInstance().IsEnabled();
    }

    int Status::GetMode()
    {
        if ( frc::DriverStation::GetInstance().IsDisabled() ) {
            return Mode::DISABLED;
        }
        if ( frc::DriverStation::GetInstance().IsOperatorControl() ) {
            return Mode::TELEOP;
        }
        if ( frc::DriverStation::GetInstance().IsAutonomous() ) {
            return Mode::AUTONOMOUS;
        }
        if ( frc::DriverStation::GetInstance().IsTest() ) {
            return Mode::TEST;
        }
        return Mode::INVALID;
    }

    int Status::GetAlliance()
    {
        switch ( frc::DriverStation::GetInstance().GetAlliance() ) {
        case frc::DriverStation::Alliance::kRed:
            return Alliance::RED;
        case frc::DriverStation::Alliance::kBlue:
            return Alliance::BLUE;
        case frc::DriverStation::Alliance::kInvalid:
            return Alliance::NONE;
        }
        return Alliance::NONE;
    }
}
