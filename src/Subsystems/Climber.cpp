#include "Climber.h"
#include "../RobotMap.h"

#include "Commands/TeleopDrive.h"

#include "CardinalDash/VictorSP.h"

Climber::Climber() : Subsystem ( "Climber" )
{
    ClimberVictor = std::make_unique<CardinalDash::VictorSP> ( MOTOR_CLIMBER );
}

void Climber::InitDefaultCommand()
{
    //SetDefaultCommand(new TeleopDrive());
}

void Climber::Set ( double speed )
{
    ClimberVictor->Set ( speed );
}
