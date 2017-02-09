#include "TeleopDrive.h"

#include "CommandBase.h"

TeleopDrive::TeleopDrive() : CommandBase ( "TeleopDrive" )
{
    Requires ( CommandBase::drivetrain.get() );
    Requires ( CommandBase::gearBox.get() );
}

void TeleopDrive::Initialize()
{

}

void TeleopDrive::Execute()
{
    CommandBase::drivetrain->Set ( CommandBase::oi->GetLeftJoystick(),
                                   CommandBase::oi->GetRightJoystick() );
    CommandBase::drivetrain->Shift ( CommandBase::oi->GetShift() );

    CommandBase::gearBox->Set ( CommandBase::oi->GetIntake() );
    CommandBase::gearBox->SetLifter ( CommandBase::oi->GetLifter() );
    CommandBase::gearBox->SetGripper ( CommandBase::oi->GetGripper() );
}

bool TeleopDrive::IsFinished()
{
    return false;
}

void TeleopDrive::End()
{

}

void TeleopDrive::Interrupted()
{

}
