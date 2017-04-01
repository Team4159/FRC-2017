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
    std::cout << "Drive distance " << driveDistance << std::endl;
    CommandBase::drivetrain->ResetAngle();
    CommandBase::drivetrain->EnablePID();
    CommandBase::drivetrain->EnableTurnPID();
    CommandBase::drivetrain->Set ( driveDistance, driveDistance );
    CommandBase::drivetrain->SetTurnAngle ( 0 );
    setpointReached = false;
}

void DriveDistance::Execute()
{
    double leftoutput = -CommandBase::drivetrain->GetLeftPIDOutput();// - CommandBase::drivetrain->GetTurnPIDOutput();

#ifdef RIGHT_ENCODER_AVAILABLE
    double rightoutput = -CommandBase::drivetrain->GetRightPIDOutput();// + CommandBase::drivetrain->GetTurnPIDOutput();
#else
    double rightoutput = -CommandBase::drivetrain->GetLeftPIDOutput();// + CommandBase::drivetrain->GetTurnPIDOutput();
#endif
    leftoutput *= 0.73*0.5;
    rightoutput *= 0.5;
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
    return setpointReached && setpointTimer.Get() > 0.1;
}

void DriveDistance::End()
{
    CommandBase::drivetrain->DisablePID();
    CommandBase::drivetrain->DisableTurnPID();
    CommandBase::drivetrain->SetRaw ( 0, 0, false );
    std::cout << "Finished drivedistance" << std::endl;
}

void DriveDistance::Interrupted()
{

}
