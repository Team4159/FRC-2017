#ifndef DRIVE_TO_PEG_H
#define DRIVE_TO_PEG_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveToPeg : public CommandBase
{
    public:
        DriveToPeg();
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End() override;
        void Interrupted() override;
    private:
        std::shared_ptr<NetworkTable> table;
};

#endif // DRIVE_TO_PEG_H