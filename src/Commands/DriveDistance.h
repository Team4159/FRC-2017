#ifndef DRIVE_DISTANCE_H
#define DRIVE_DISTANCE_H

#include "../CommandBase.h"

class DriveDistance: public CommandBase
{
    public:
        DriveDistance(double distance);
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End() override;
        void Interrupted() override;
	private:
		double driveDistance;
		frc::Timer setpointTimer;
		bool setpointReached;
};

#endif  // DRIVE_DISTANCE_H
