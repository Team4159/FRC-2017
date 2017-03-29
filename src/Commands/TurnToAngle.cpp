#include "TurnToAngle.h"

#include <math.h>

#include "CommandBase.h"

TurnToAngle::TurnToAngle(double angle) : CommandBase ( "TurnToAngle" )
{
    Requires ( CommandBase::drivetrain.get() );
	targetAngle = angle;
}

void TurnToAngle::Initialize()
{
   	CommandBase::drivetrain->DisablePID();
	CommandBase::drivetrain->EnableTurnPID();
	CommandBase::drivetrain->SetTurnAngle(targetAngle);
}

void TurnToAngle::Execute()
{
	CommandBase::drivetrain->SetRaw(-CommandBase::drivetrain->GetTurnPIDOutput(), CommandBase::drivetrain->GetTurnPIDOutput(), false);
}

bool TurnToAngle::IsFinished()
{
    return CommandBase::drivetrain->GetTurnDone();
}

void TurnToAngle::End()
{
	CommandBase::drivetrain->SetRaw(0, 0, false);
	CommandBase::drivetrain->DisableTurnPID();
}

void TurnToAngle::Interrupted()
{
	
}