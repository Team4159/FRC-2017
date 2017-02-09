#include "GearBox.h"
#include "../RobotMap.h"

#include "Commands/TeleopDrive.h"

#include <DoubleSolenoid.h>

#include "CardinalDash/VictorSP.h"

GearBox::GearBox() : Subsystem ( "GearBox" )
{
    IntakeVictor = std::make_unique<CardinalDash::VictorSP> ( MOTOR_INTAKE );

    lifterSolenoid = std::make_unique<frc::DoubleSolenoid> ( 4, 5 );
    gripperSolenoid = std::make_unique<frc::DoubleSolenoid> ( 6, 7 );
}

void GearBox::InitDefaultCommand()
{
    //SetDefaultCommand(new TeleopDrive());
}

void GearBox::Set ( double speed )
{
    IntakeVictor->Set ( speed );
}

void GearBox::SetLifter ( bool up )
{
    lifterSolenoid->Set ( up ? frc::DoubleSolenoid::Value::kForward :
                          frc::DoubleSolenoid::Value::kReverse );
}

void GearBox::SetGripper ( bool closed )
{
    gripperSolenoid->Set ( closed ? frc::DoubleSolenoid::Value::kForward :
                           frc::DoubleSolenoid::Value::kReverse );
}
