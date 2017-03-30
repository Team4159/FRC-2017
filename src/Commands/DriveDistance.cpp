#include "DriveDistance.h"

#include "CommandBase.h"
#include <cmath>
#define RIGHT_ENCODER_AVAILABLE
DriveDistance::DriveDistance ( double distance ) : CommandBase ( "DriveDistance" )
{
    Requires ( CommandBase::drivetrain.get() );
    driveDistance = distance;
}

void DriveDistance::Initialize()
{
    CommandBase::drivetrain->ResetAngle();
    CommandBase::drivetrain->EnablePID();
    CommandBase::drivetrain->EnableTurnPID();
    CommandBase::drivetrain->Set ( driveDistance, driveDistance );
    CommandBase::drivetrain->SetTurnAngle ( 0 );
    setpointReached = false;
}

void DriveDistance::Execute()
{
    double leftoutput = -CommandBase::drivetrain->GetLeftPIDOutput() - CommandBase::drivetrain->GetTurnPIDOutput();

#ifdef RIGHT_ENCODER_AVAILABLE
    double rightoutput = -CommandBase::drivetrain->GetRightPIDOutput() + CommandBase::drivetrain->GetTurnPIDOutput();
#else
    double rightoutput = -CommandBase::drivetrain->GetLeftPIDOutput() + CommandBase::drivetrain->GetTurnPIDOutput();
#endif
    // Scale outputs down to fit in range -1 to 1
    if ( std::fabs ( leftoutput ) > 1 || std::fabs ( rightoutput ) > 1 ) {
        // Scale larger output to 1 and keep ratio of two outputs the same
        double scalefactor = 1.0/std::max ( std::fabs ( leftoutput ), std::fabs ( rightoutput ) );
        leftoutput *= scalefactor;
        rightoutput*= scalefactor;
    }
    CommandBase::drivetrain->SetRaw ( leftoutput, rightoutput, false );
    if ( CommandBase::drivetrain->DistancePIDDone() ) {
        if ( !setpointReached ) {
            setpointTimer.Start();
            setpointReached = true;
        }
    } else {
        setpointTimer.Stop();
        setpointTimer.Reset();
        setpointReached = false;
    }
}

bool DriveDistance::IsFinished()
{
    return setpointReached && setpointTimer.Get() > 1.0;
}

void DriveDistance::End()
{
    CommandBase::drivetrain->DisablePID();
    CommandBase::drivetrain->DisableTurnPID();
}

void DriveDistance::Interrupted()
{

}
