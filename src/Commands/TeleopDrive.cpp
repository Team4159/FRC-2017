#include "TeleopDrive.h"

#include <math.h>

#include "CommandBase.h"

TeleopDrive::TeleopDrive() : CommandBase ( "TeleopDrive" )
{
    Requires ( CommandBase::drivetrain.get() );
    Requires ( CommandBase::gearBox.get() );
}

void TeleopDrive::Initialize()
{
    CommandBase::drivetrain->DisablePID();
}

void TeleopDrive::Execute()
{
    CommandBase::drivetrain->SetRaw ( pow ( CommandBase::oi->GetLeftJoystick(), 2 ) * ( CommandBase::oi->GetLeftJoystick() < 0 ? -1 : 1 ),
                                      pow ( CommandBase::oi->GetRightJoystick(), 2 ) * ( CommandBase::oi->GetRightJoystick() < 0 ? -1 : 1 ) );
    CommandBase::drivetrain->Shift ( CommandBase::oi->GetShift() );

    CommandBase::gearBox->Set ( CommandBase::oi->GetIntake() );
    CommandBase::gearBox->SetLifter ( CommandBase::oi->GetLifter() );
    CommandBase::gearBox->SetGripper ( CommandBase::oi->GetGripper() );

    CommandBase::climber->Set ( CommandBase::oi->GetClimber() );
}

bool TeleopDrive::IsFinished()
{
    return false;
}

void TeleopDrive::End()
{
    CommandBase::drivetrain->DisablePID();
}

void TeleopDrive::Interrupted()
{

}
