#include "EjectGear.h"

#include "CommandBase.h"

EjectGear::EjectGear() : CommandBase ( "EjectGear" )
{
    Requires ( CommandBase::gearBox.get() );
    Requires ( CommandBase::drivetrain.get() );
}

void EjectGear::Initialize()
{
    timer.Start();
    CommandBase::gearBox->SetLifter ( true );
    CommandBase::gearBox->SetGripper ( true );
}

void EjectGear::Execute()
{
	// Eject gear and start reversing after gear tray lifts up
    if ( timer.Get() < 1.0 ) {
        CommandBase::gearBox->SetGripper ( false );
		CommandBase::drivetrain->SetRaw ( 1, 1, false );
    }
	
}

bool EjectGear::IsFinished()
{
    // Stop after reversing for two seconds
    return timer.Get() < 3.0;
}

void EjectGear::End()
{
    CommandBase::drivetrain->SetRaw ( 0, 0, false );
}

void EjectGear::Interrupted()
{
    End();
}
