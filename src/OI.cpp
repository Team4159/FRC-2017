#include "OI.h"

#include <WPILib.h>

OI::OI()
{
#ifndef OI_XBOX_PRIMARY
    leftStick = std::make_unique<frc::Joystick> ( 0 );
    rightStick = std::make_unique<frc::Joystick> ( 1 );
#else
    primaryController = std::make_unique<frc::XboxController> ( 0 );
#endif
    secondaryStick = std::make_unique<frc::Joystick> ( 2 );
}

double OI::GetLeftJoystick()
{
#ifndef OI_XBOX_PRIMARY
    return leftStick->GetY();
#else
    return primaryController->GetY ( frc::GenericHID::JoystickHand::kLeftHand );
#endif
}

double OI::GetRightJoystick()
{
#ifndef OI_XBOX_PRIMARY
    return rightStick->GetY();
#else
    return primaryController->GetY ( frc::GenericHID::JoystickHand::kRightHand );
#endif
}

double OI::GetIntake()
{
    return secondaryStick->GetY();
}

double OI::GetClimber()
{
    if ( !secondaryStick->GetRawButton ( 6 ) ) {
        return 0;
    }
    return secondaryStick->GetZ();
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
#ifndef OI_XBOX_PRIMARY
    if ( rightStick->GetRawButton ( 3 ) ) {
        shifterPosition = true;
    }
    if ( rightStick->GetRawButton ( 2 ) ) {
        shifterPosition = false;
    }
#else
    if ( primaryController->GetBumper ( frc::GenericHID::JoystickHand::kLeftHand ) ) {
        shifterPosition = true;
    }
    if ( primaryController->GetBumper ( frc::GenericHID::JoystickHand::kRightHand ) ) {
        shifterPosition = false;
    }
#endif
    return shifterPosition;
}

bool OI::GetGripper()
{
    return !secondaryStick->GetTrigger();
}


bool OI::GetRecording()
{
    return leftStick->GetTrigger() && rightStick->GetTrigger();
}
