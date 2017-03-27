#include "AutoGear.h"

#include "CommandBase.h"

#include "TurnToAngle.h"
#include "DriveDistance.h"
#include "DeliverGear.h"

AutoGear::AutoGear(int peg) : CommandGroup ( "AutoGear" )
{
	if (peg==0){
		// Middle peg
		// Use PID to move halfway
		AddSequential(new DriveDistance(30));
		
	}
	else if (peg==-1){
		// Left peg
		// Drive forward to baseline then turn 60 degrees
		AddSequential(new DriveDistance(65));
		AddSequential(new TurnToAngle(60));
	}
	else if (peg==1){
		// Right peg
		// Same as left peg except turn direction is reversed
		AddSequential(new DriveDistance(65));
		AddSequential(new TurnToAngle(-60));
	}
	// Go to peg, drop off gear, and reverse
	AddSequential(new DeliverGear());
}

