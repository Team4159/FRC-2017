#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <Commands/Subsystem.h>
#include <math.h>
#include <DoubleSolenoid.h>
#include <Encoder.h>
#include <PIDController.h>
#include "CardinalDash/VictorSP.h"

#include "WPILib.h"

class Drivetrain : public Subsystem
{
    public:
        Drivetrain();
        void InitDefaultCommand();
        void Set ( double left, double right );
        void SetRaw ( double left, double right, bool currentLimit = true );
        void SetAdd ( double left, double right );
        void SetLeftRaw ( double left );
        void SetRightRaw ( double right );
        void Shift ( bool high );

        void EnablePID();
        void DisablePID();

        struct DrivetrainVoltage {
            double left;
            double right;

            DrivetrainVoltage ( double l, double r )
            {
                left = l;
                right = r;
            }
        };

        void SetVoltage ( DrivetrainVoltage v );
        double GetVoltage(); // Get current robot voltage
        DrivetrainVoltage GetOutputVoltage();
        double GetLeftVoltage();
        double GetRightVoltage();

    private:
        // Voltage max of battery, if it was 12 then all motors would drive
        // slower when actual voltage > 12. This is because of the division step
        // in SetVoltage which can lead to slower than 100% motor setpoints
        const int VOLTAGE_MAX = 13;

        const double ENCODER_PULSE_PER_ROTATION = 360;
        const double ENCODER_WHEEL_DIAMETER = 4; // inches
        const double ENCODER_WHEEL_CIRCUMFERENCE = ENCODER_WHEEL_DIAMETER * M_PI;
        const double ENCODER_DISTANCE_PER_PULSE = ENCODER_WHEEL_CIRCUMFERENCE / ENCODER_PULSE_PER_ROTATION;

        const double PID_LEFT_P = 0.15;
        const double PID_LEFT_I = 0.0;
        const double PID_LEFT_D = 0.01;
        const double PID_LEFT_F = 0.05;

        const double PID_RIGHT_P = 0.15;
        const double PID_RIGHT_I = 0.0;
        const double PID_RIGHT_D = 0.01;
        const double PID_RIGHT_F = 0.05;

        double lastLeft = 0;
        double lastLeftGhost = 0;
        double lastRight = 0;
        double lastRightGhost = 0;

        const double MAX_ACCEL = 0.005 / 2;
        const double MAX_GHOST_ACCEL = MAX_ACCEL * 15;

        static std::unique_ptr<PowerDistributionPanel> pdp;

        std::unique_ptr<CardinalDash::VictorSP> LeftVictor;
        std::unique_ptr<CardinalDash::VictorSP> RightVictor;

        std::unique_ptr<frc::DoubleSolenoid> LeftSolenoid;
        std::unique_ptr<frc::DoubleSolenoid> RightSolenoid;

        std::unique_ptr<frc::Encoder> LeftEncoder;
        std::unique_ptr<frc::Encoder> RightEncoder;

        std::unique_ptr<frc::PIDController> LeftPID;
        std::unique_ptr<frc::PIDController> RightPID;

        DrivetrainVoltage voltage = DrivetrainVoltage ( 0, 0 );

        static double GetLeftVoltage ( void* instance );
        static double GetRightVoltage ( void* instance );
        static double GetEncoderValue ( void* instance );

};

#endif  // DRIVETRAIN_H
