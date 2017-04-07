#include "AutoGear.h"

#include "CommandBase.h"

#include "TurnToAngle.h"
#include "DriveDistance.h"
#include "DeliverGear.h"

AutoGear::AutoGear ( int peg, bool diagonal ) : CommandGroup ( "AutoGear" )
{
    if ( peg==0 ) {
        // Middle peg
        // Use PID to move halfway
        AddSequential ( new DriveDistance ( 60 ) );

    } else if ( peg==-1 ) {
        // Left peg
        // Drive forward to baseline then turn 60 degrees
        AddSequential ( new DriveDistance ( 100 ) );
        AddSequential ( new TurnToAngle ( 60 ) );
    } else if ( peg==1 ) {
        // Right peg
        // Same as left peg except turn direction is reversed
        AddSequential ( new DriveDistance ( 95 ) );
        AddSequential ( new TurnToAngle ( -60 ) );
    }
    // Go to peg, drop off gear, and reverse
    AddSequential ( new DeliverGear() );

    if ( peg!=0 ) {
        // Turn forward and go to center of field
        AddSequential ( new TurnToAngle ( 60* ( peg==1?1:-1 ) ) );

        if ( diagonal ) {
            // Move forward, then turn and go diagonally across field
            AddSequential ( new DriveDistance ( 90 ) );
            AddSequential ( new TurnToAngle ( -40* ( peg==1?1:-1 ) ) );
            AddSequential ( new DriveDistance ( 200 ) );
        } else {
            // Move forward
            AddSequential ( new DriveDistance ( 170 ) );
        }
    }
}
