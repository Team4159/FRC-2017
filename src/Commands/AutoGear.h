#ifndef AUTO_GEAR_H
#define AUTO_GEAR_H

#include "../CommandBase.h"

class AutoGear: public CommandGroup
{
    public:
        AutoGear ( int peg, bool diagonal );
};

#endif  // AUTO_GEAR_H
