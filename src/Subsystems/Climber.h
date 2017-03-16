#ifndef CLIMBER_H
#define CLIMBER_H

#include <Commands/Subsystem.h>
#include <DoubleSolenoid.h>

#include "CardinalDash/VictorSP.h"

class Climber : public Subsystem
{
    private:
        std::unique_ptr<CardinalDash::VictorSP> ClimberVictor;
    public:
        Climber();
        void InitDefaultCommand();
        void Set ( double speed );
};

#endif  // CLIMBER_H
