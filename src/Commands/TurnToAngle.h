#ifndef TURN_TO_ANGLE_H
#define TURN_TO_ANGLE_H

#include "../CommandBase.h"

class TurnToAngle: public CommandBase
{
    public:
        TurnToAngle ( double angle );
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End() override;
        void Interrupted() override;
    private:
        double targetAngle;
};

#endif  // TURN_TO_ANGLE_H
