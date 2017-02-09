#ifndef TELEOP_DRIVE_H
#define TELEOP_DRIVE_H

#include "../CommandBase.h"

class TeleopDrive: public CommandBase
{
    public:
        TeleopDrive();
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End() override;
        void Interrupted() override;
};

#endif  // TELEOP_DRIVE_H
