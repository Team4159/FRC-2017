#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <Commands/Subsystem.h>
#include <DoubleSolenoid.h>
#include "CardinalDash/VictorSP.h"

#include "WPILib.h"

class Drivetrain : public Subsystem
{
    public:
        Drivetrain();
        void InitDefaultCommand();
        void Set ( double left, double right );
        void Shift ( bool high );

        struct DrivetrainVoltage {
            double left;
            double right;

            DrivetrainVoltage ( double l, double r ) {
                left = l;
                right = r;
            }
        };

        void SetVoltage ( DrivetrainVoltage v );
        double GetVoltage(); // Get current robot voltage
        DrivetrainVoltage GetOutputVoltage();
        double GetLeftVoltage();
        double GetRightVoltage();
        static double GetLeftVoltage(void* instance);
        static double GetRightVoltage(void* instance);
    private:
        // Voltage max of battery, if it was 12 then all motors would drive
        // slower when actual voltage > 12. This is because of the division step
        // in SetVoltage which can lead to slower than 100% motor setpoints
        const int VOLTAGE_MAX = 13;

        static std::unique_ptr<PowerDistributionPanel> pdp;

        std::unique_ptr<CardinalDash::VictorSP> LeftVictor;
        std::unique_ptr<CardinalDash::VictorSP> RightVictor;

        std::unique_ptr<frc::DoubleSolenoid> LeftSolenoid;
        std::unique_ptr<frc::DoubleSolenoid> RightSolenoid;

        DrivetrainVoltage voltage = DrivetrainVoltage ( 0, 0 );
};

#endif  // DRIVETRAIN_H
