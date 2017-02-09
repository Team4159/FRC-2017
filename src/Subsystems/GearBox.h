#ifndef GEARBOX_H
#define GEARBOX_H

#include <Commands/Subsystem.h>
#include <DoubleSolenoid.h>

#include "CardinalDash/VictorSP.h"

class GearBox : public Subsystem
{
    private:
        std::unique_ptr<CardinalDash::VictorSP> IntakeVictor;
        std::unique_ptr<frc::DoubleSolenoid> lifterSolenoid;
        std::unique_ptr<frc::DoubleSolenoid> gripperSolenoid;
    public:
        GearBox();
        void InitDefaultCommand();
        void Set ( double speed );
        void SetLifter ( bool up );
        void SetGripper ( bool closed );
};

#endif  // GEARBOX_H