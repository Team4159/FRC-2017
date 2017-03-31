#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <Commands/Subsystem.h>
#include <math.h>
#include <DoubleSolenoid.h>
#include <Encoder.h>
#include <PIDController.h>
#include "CardinalDash/VictorSP.h"
#include "PIDOutputReceiver.h"

#include "WPILib.h"
#include "AHRS.h"

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

        double GetLeftPIDOutput();
        double GetRightPIDOutput();
        bool DistancePIDDone();

        void SetTurnAngle ( double value );
        void EnableTurnPID();
        void DisableTurnPID();
        double GetAngle();
        void ResetAngle();
        double GetTurnPIDOutput();
        bool GetTurnDone();
        double GetTurnPIDError();
        double GetLeftEncoderDistance();
		double GetRightEncoderDistance();
		double GetLeftMotor();
		double GetRightMotor();
    private:
        const double ENCODER_PULSE_PER_ROTATION = 360;
        const double ENCODER_WHEEL_DIAMETER = 4; // inches
        const double ENCODER_WHEEL_CIRCUMFERENCE = ENCODER_WHEEL_DIAMETER * M_PI;
        const double ENCODER_DISTANCE_PER_PULSE = ENCODER_WHEEL_CIRCUMFERENCE / ENCODER_PULSE_PER_ROTATION;

        const double PID_LEFT_P = 0.1;
        const double PID_LEFT_I = 0.0;
        const double PID_LEFT_D = 0.01;
        const double PID_LEFT_F = 0.0;
        const double PID_LEFT_TOLERANCE = 2;

        const double PID_RIGHT_P = 0.1;
        const double PID_RIGHT_I = 0.0;
        const double PID_RIGHT_D = 0.01;
        const double PID_RIGHT_F = 0;
        const double PID_RIGHT_TOLERANCE = 2;

        const double PID_TURN_P = 0.03;
        const double PID_TURN_I = 0;
        const double PID_TURN_D = 0.1;
        const double PID_TURN_F = 0;
        const double PID_TURN_TOLERANCE = 10;

        double lastLeft = 0;
        double lastLeftGhost = 0;
        double lastRight = 0;
        double lastRightGhost = 0;

        const double ACCEL_MULT = 1.2;

        const double MAX_ACCEL = 0.0025 * ACCEL_MULT;
        const double MAX_GHOST_ACCEL = 15 * MAX_ACCEL;

        static std::unique_ptr<PowerDistributionPanel> pdp;

        std::unique_ptr<CardinalDash::VictorSP> LeftVictor;
        std::unique_ptr<CardinalDash::VictorSP> RightVictor;

        std::unique_ptr<frc::DoubleSolenoid> LeftSolenoid;
        std::unique_ptr<frc::DoubleSolenoid> RightSolenoid;

        std::unique_ptr<frc::Encoder> LeftEncoder;
        std::unique_ptr<frc::Encoder> RightEncoder;

        std::unique_ptr<frc::PIDController> LeftPID;
        std::unique_ptr<frc::PIDController> RightPID;
        std::unique_ptr<PIDOutputReceiver> LeftOutput;
        std::unique_ptr<PIDOutputReceiver> RightOutput;

        std::unique_ptr<frc::PIDController> TurnPID;
        std::unique_ptr<AHRS> ahrs;
        std::unique_ptr<PIDOutputReceiver> TurnOutput;

        static double GetEncoderValue ( void* instance );

};

#endif  // DRIVETRAIN_H
