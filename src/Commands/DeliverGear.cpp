#include "DeliverGear.h"

#include "CommandBase.h"
#include "DriveToPeg.h"
#include "EjectGear.h"

DeliverGear::DeliverGear() : CommandGroup ( "DeliverGear" )
{
    AddSequential ( new DriveToPeg() );
    AddSequential ( new EjectGear() );
}