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
	frc::SmartDashboard::PutString("Status", "Turn to angle");
   	CommandBase::drivetrain->DisablePID();
	CommandBase::drivetrain->EnableTurnPID();
	CommandBase::drivetrain->SetTurnAngle(targetAngle);
}

void TurnToAngle::Execute()
{
	frc::SmartDashboard::PutNumber("Turn", CommandBase::drivetrain->GetTurnPIDOutput());
	frc::SmartDashboard::PutNumber("Error", CommandBase::drivetrain->GetTurnPIDError());
	frc::SmartDashboard::PutNumber("L Motor", -CommandBase::drivetrain->GetTurnPIDOutput());
	frc::SmartDashboard::PutNumber("R Motor", CommandBase::drivetrain->GetTurnPIDOutput());
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