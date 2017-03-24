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
    double outputMagnitude = -0.3;
    double curve = angle/52*2;
	// Sensitivity should be higher when farther away 
	// Causes robot to eventually line up with peg
    double m_sensitivity = 0.2+(distance/100.0);
    double leftOutput, rightOutput;
    double value = std::log ( fabs ( curve ) );
    double ratio = ( value - m_sensitivity ) / ( value + m_sensitivity );
    if ( ratio == 0 ) {
        ratio = .0000000001;
    }
    if ( curve < 0 ) {
        leftOutput = outputMagnitude / ratio;
        rightOutput = outputMagnitude;
    } else if ( curve > 0 ) {
        leftOutput = outputMagnitude;
        rightOutput = outputMagnitude / ratio;
    } else {
        leftOutput = outputMagnitude;
        rightOutput = outputMagnitude;
    }
    if ( distance==-1 ) {
        return;
    }
    CommandBase::drivetrain->SetRaw ( leftOutput, rightOutput );
}

bool DriveToPeg::IsFinished()
{
    double distance = table->GetNumber ( "distance", -1 );
    return ( distance!=-1 && distance<26 );
}

void DriveToPeg::End()
{
    CommandBase::drivetrain->SetRaw ( 0, 0 );
}

void DriveToPeg::Interrupted()
{
    End();
}
