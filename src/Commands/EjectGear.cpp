#include "EjectGear.h"

#include "CommandBase.h"

EjectGear::EjectGear() : CommandBase ( "EjectGear" )
{
    Requires ( CommandBase::gearBox.get() );
    Requires ( CommandBase::drivetrain.get() );
}

void EjectGear::Initialize()
{
    timer.Reset();
    timer.Start();
    CommandBase::gearBox->SetLifter ( true );
    CommandBase::gearBox->SetGripper ( true );
}

void EjectGear::Execute()
{
    // Eject gear and start reversing after gear tray lifts up
    if ( timer.Get() > 1.0 ) {
        CommandBase::gearBox->SetGripper ( false );
        if ( timer.Get() < 1.8 && timer.Get() > 1.3 ) {
            CommandBase::drivetrain->SetRaw ( 0.4, 0.4, false );
        } else {
            CommandBase::drivetrain->SetRaw ( 0.2, 0.2, false );
        }
    }

}

bool EjectGear::IsFinished()
{
    // Stop after reversing for two seconds
    return timer.Get() > 2;
}

void EjectGear::End()
{
    CommandBase::drivetrain->SetRaw ( 0, 0, false );
    CommandBase::gearBox->SetLifter ( false );
    CommandBase::gearBox->SetGripper ( true );
}

void EjectGear::Interrupted()
{
    End();
}
