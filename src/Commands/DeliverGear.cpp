#include "DeliverGear.h"

#include "CommandBase.h"
#include "DriveToPeg.h"
#include "EjectGear.h"

DeliverGear::DeliverGear() : CommandGroup ( "DeliverGear" )
{
    CommandBase::gearBox->SetLifter ( false );
    CommandBase::gearBox->SetGripper ( true );
    AddSequential ( new DriveToPeg() );
    AddSequential ( new EjectGear() );
}