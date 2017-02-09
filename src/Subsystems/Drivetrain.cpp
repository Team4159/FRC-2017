#include "Drivetrain.h"
#include "../RobotMap.h"

#include "Commands/TeleopDrive.h"

#include "CardinalDash/VictorSP.h"

#include <DoubleSolenoid.h>

Drivetrain::Drivetrain() : Subsystem ( "Drivetrain" )
{
    LeftVictor = std::make_unique<CardinalDash::VictorSP> ( MOTOR_LEFT_DRIVE );
    RightVictor = std::make_unique<CardinalDash::VictorSP> ( MOTOR_RIGHT_DRIVE );

    leftSolenoid = std::make_unique<frc::DoubleSolenoid> ( 0, 1 );
    rightSolenoid = std::make_unique<frc::DoubleSolenoid> ( 2, 3 );
}

void Drivetrain::InitDefaultCommand()
{
    SetDefaultCommand ( new TeleopDrive() );
}

void Drivetrain::Set ( double left, double right )
{
    // DrivetrainVoltage v;
    // v.left = left * VOLTAGE_MAX ;
    // v.right = right * VOLTAGE_MAX ;
    // this->SetVoltage(v);
    LeftVictor->Set ( left );
    RightVictor->Set ( right );
}

void Drivetrain::Shift ( bool high )
{
    leftSolenoid->Set ( high ? frc::DoubleSolenoid::Value::kForward :
                        frc::DoubleSolenoid::Value::kReverse );
    rightSolenoid->Set ( high ? frc::DoubleSolenoid::Value::kForward :
                         frc::DoubleSolenoid::Value::kReverse );
}
