#ifndef EJECT_GEAR_H
#define EJECT_GEAR_H

#include "../CommandBase.h"

class EjectGear: public CommandBase
{
    public:
        EjectGear();
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End() override;
        void Interrupted() override;
    private:
        Timer timer;
};

#endif  // EJECT_GEAR_H
