#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <Commands/Subsystem.h>
#include <DoubleSolenoid.h>
#include "CardinalDash/VictorSP.h"

class Drivetrain : public Subsystem
{
    private:
        const int VOLTAGE_MAX = 12;

        struct DrivetrainVoltage {
            double left;
            double right;
        };

        void SetVoltage ( DrivetrainVoltage v );
        double GetVoltage(); // Get current robot voltage
        DrivetrainVoltage GetOutputVoltage();

        std::unique_ptr<CardinalDash::VictorSP> LeftVictor;
        std::unique_ptr<CardinalDash::VictorSP> RightVictor;

        std::unique_ptr<frc::DoubleSolenoid> leftSolenoid;
        std::unique_ptr<frc::DoubleSolenoid> rightSolenoid;
    public:
        Drivetrain();
        void InitDefaultCommand();
        void Set ( double left, double right );
        void Shift ( bool high );
};

#endif  // DRIVETRAIN_H
