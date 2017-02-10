#include "GearBox.h"
#include "../RobotMap.h"

#include "Commands/TeleopDrive.h"

#include <DoubleSolenoid.h>

#include "CardinalDash/VictorSP.h"

GearBox::GearBox() : Subsystem ( "GearBox" )
{
    IntakeVictor = std::make_unique<CardinalDash::VictorSP> ( MOTOR_INTAKE );

    LifterSolenoidLeft = std::make_unique<frc::DoubleSolenoid> ( SOLENOID_LIFTER_LEFT_A, SOLENOID_LIFTER_LEFT_B );
    LifterSolenoidRight = std::make_unique<frc::DoubleSolenoid> ( SOLENOID_LIFTER_RIGHT_A, SOLENOID_LIFTER_RIGHT_B );
    GripperSolenoid = std::make_unique<frc::DoubleSolenoid> ( SOLENOID_GRIPPER_A, SOLENOID_GRIPPER_B );
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
    LifterSolenoidLeft->Set ( up ? frc::DoubleSolenoid::Value::kForward :
                              frc::DoubleSolenoid::Value::kReverse );
    LifterSolenoidRight->Set ( up ? frc::DoubleSolenoid::Value::kForward :
                               frc::DoubleSolenoid::Value::kReverse );
}

void GearBox::SetGripper ( bool closed )
{
    GripperSolenoid->Set ( closed ? frc::DoubleSolenoid::Value::kForward :
                           frc::DoubleSolenoid::Value::kReverse );
}
