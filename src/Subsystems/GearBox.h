#ifndef GEARBOX_H
#define GEARBOX_H

#include <Commands/Subsystem.h>
#include <DoubleSolenoid.h>

#include "CardinalDash/VictorSP.h"

#include "WPILib.h"

class GearBox : public Subsystem
{
    private:
        static std::unique_ptr<PowerDistributionPanel> pdp;

        const int INTAKE_PDP_PORT = 12;

        std::unique_ptr<CardinalDash::VictorSP> IntakeVictor;
        std::unique_ptr<frc::DoubleSolenoid> LifterSolenoidLeft;
        std::unique_ptr<frc::DoubleSolenoid> LifterSolenoidRight;
        std::unique_ptr<frc::DoubleSolenoid> GripperSolenoid;
    public:
        GearBox();
        void InitDefaultCommand();
        void Set ( double speed );
        void SetLifter ( bool up );
        void SetGripper ( bool closed );
};

#endif  // GEARBOX_H
