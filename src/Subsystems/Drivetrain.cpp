#include "Drivetrain.h"
#include "../RobotMap.h"

#include "Commands/TeleopDrive.h"
#include "CardinalDash/VictorSP.h"
#include "CardinalDash/Dashboard.h"

#include <DoubleSolenoid.h>

std::unique_ptr<PowerDistributionPanel> Drivetrain::pdp = std::make_unique<PowerDistributionPanel>();

Drivetrain::Drivetrain() : Subsystem ( "Drivetrain" )
{
    LeftVictor = std::make_unique<CardinalDash::VictorSP> ( MOTOR_LEFT_DRIVE );
    RightVictor = std::make_unique<CardinalDash::VictorSP> ( MOTOR_RIGHT_DRIVE );

    LeftSolenoid = std::make_unique<frc::DoubleSolenoid> ( SOLENOID_SHIFTER_LEFT_A, SOLENOID_SHIFTER_LEFT_B );
    RightSolenoid = std::make_unique<frc::DoubleSolenoid> ( SOLENOID_SHIFTER_RIGHT_A, SOLENOID_SHIFTER_RIGHT_B );

    CardinalDash::Dashboard::Subscribe(std::string("subsystems/drivetrain/leftvoltage"), &GetLeftVoltage, this);
    CardinalDash::Dashboard::Subscribe(std::string("subsystems/drivetrain/rightvoltage"), &GetRightVoltage, this);
}

void Drivetrain::InitDefaultCommand()
{
    SetDefaultCommand ( new TeleopDrive() );
}

void Drivetrain::Set ( double left, double right )
{
    DrivetrainVoltage v = DrivetrainVoltage ( left * VOLTAGE_MAX, right * VOLTAGE_MAX );
    SetVoltage ( v );
}

void Drivetrain::Shift ( bool high )
{
    LeftSolenoid->Set ( high ? frc::DoubleSolenoid::Value::kForward :
                        frc::DoubleSolenoid::Value::kReverse );
    RightSolenoid->Set ( high ? frc::DoubleSolenoid::Value::kForward :
                         frc::DoubleSolenoid::Value::kReverse );
}

void Drivetrain::SetVoltage ( DrivetrainVoltage v )
{
    voltage = v;

    double robotVoltage = GetVoltage();

    LeftVictor->Set ( v.left / robotVoltage );
    RightVictor->Set ( v.right / robotVoltage );
}

double Drivetrain::GetVoltage()
{
    return pdp->GetVoltage();
}

Drivetrain::DrivetrainVoltage Drivetrain::GetOutputVoltage()
{
    return voltage;
}

double Drivetrain::GetLeftVoltage()
{
    return GetOutputVoltage().left;
}

double Drivetrain::GetRightVoltage()
{
    return GetOutputVoltage().right;
}

double Drivetrain::GetLeftVoltage(void* instance)
{
    return ( ( Drivetrain* ) instance )->GetLeftVoltage();
}

double Drivetrain::GetRightVoltage(void* instance)
{
    return ( ( Drivetrain* ) instance )->GetRightVoltage();
}
