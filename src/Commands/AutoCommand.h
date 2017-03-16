#ifndef AUTO_COMMAND_H
#define AUTO_COMMAND_H

#include "../CommandBase.h"

class AutoCommand: public CommandBase
{
    public:
        AutoCommand();
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End() override;
        void Interrupted() override;
};

#endif  // AUTO_COMMAND_H
