#include "DriveToPeg.h"

#include "CommandBase.h"

DriveToPeg::DriveToPeg() : CommandBase ( "DriveToPeg" )
{
    Requires ( CommandBase::drivetrain.get() );
}

void DriveToPeg::Initialize()
{
    table = NetworkTable::GetTable ( "pi/target" );
	// Lower gear tray to prevent blockage of camera
    CommandBase::gearBox->SetLifter ( false );
    CommandBase::gearBox->SetGripper ( true );
}

void DriveToPeg::Execute()
{
    double distance = table->GetNumber ( "distance", -1 );
    double angle = table->GetNumber ( "angle", 0 );
    if ( distance==-1 ) {
		return;
    }
    double outputMagnitude = -0.3;
	double curve = angle/70.0;
    double leftOutput = outputMagnitude - curve;
	double rightOutput = outputMagnitude + curve;

	// Scale outputs down to fit in range -1 to 1
	if (std::fabs(leftOutput) > 1 || std::fabs(rightOutput) > 1){
		// Scale larger output to 1 and keep ratio of two outputs the same
		double scalefactor = 1.0/std::max(std::fabs(leftOutput), std::fabs(rightOutput));
		leftOutput *= scalefactor;
		rightOutput*= scalefactor;
	}

    CommandBase::drivetrain->SetRaw ( leftOutput, rightOutput, false );
}

bool DriveToPeg::IsFinished()
{
    double distance = table->GetNumber ( "distance", -1 );
    return ( distance!=-1 && distance<23 );
}

void DriveToPeg::End()
{
    CommandBase::drivetrain->SetRaw ( 0, 0, false );
}

void DriveToPeg::Interrupted()
{
    End();
}
