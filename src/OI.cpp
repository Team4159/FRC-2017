#include "OI.h"

#include <WPILib.h>

OI::OI()
{
    leftStick = std::make_unique<frc::Joystick> ( 0 );
    rightStick = std::make_unique<frc::Joystick> ( 1 );
    secondaryStick = std::make_unique<frc::Joystick> ( 2 );
}

double OI::GetLeftJoystick()
{
    return leftStick->GetY();
}

double OI::GetRightJoystick()
{
    return rightStick->GetY();
}

double OI::GetIntake()
{
    return secondaryStick->GetY();
}

bool OI::GetLifter()
{
    if ( secondaryStick->GetRawButton ( 3 ) ) {
        lifterPosition = true;
    }
    if ( secondaryStick->GetRawButton ( 2 ) ) {
        lifterPosition = false;
    }

    return lifterPosition;
}

bool OI::GetShift()
{
    if ( rightStick->GetRawButton ( 3 ) ) {
        shifterPosition = true;
    }
    if ( rightStick->GetRawButton ( 2 ) ) {
        shifterPosition = false;
    }

    return shifterPosition;
}

bool OI::GetGripper()
{
    return !secondaryStick->GetTrigger();
}
