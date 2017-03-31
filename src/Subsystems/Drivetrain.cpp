#include "Drivetrain.h"
#include "../RobotMap.h"

#include "Commands/TeleopDrive.h"
#include "CardinalDash/VictorSP.h"
#include "CardinalDash/Dashboard.h"

#include "AHRS.h"

#include <DoubleSolenoid.h>

#include <cmath>

std::unique_ptr<PowerDistributionPanel> Drivetrain::pdp = std::make_unique<PowerDistributionPanel>();

Drivetrain::Drivetrain() : Subsystem ( "Drivetrain" )
{
    ahrs = std::make_unique<AHRS> ( SerialPort::kMXP );

    LeftVictor = std::make_unique<CardinalDash::VictorSP> ( MOTOR_LEFT_DRIVE );
    LeftVictor->SetInverted ( true );
    RightVictor = std::make_unique<CardinalDash::VictorSP> ( MOTOR_RIGHT_DRIVE );

    LeftSolenoid = std::make_unique<frc::DoubleSolenoid> ( SOLENOID_SHIFTER_LEFT_A, SOLENOID_SHIFTER_LEFT_B );
    RightSolenoid = std::make_unique<frc::DoubleSolenoid> ( SOLENOID_SHIFTER_RIGHT_A, SOLENOID_SHIFTER_RIGHT_B );

    LeftEncoder = std::make_unique<frc::Encoder> ( ENCODER_DRIVE_LEFT_A, ENCODER_DRIVE_LEFT_B );
    RightEncoder = std::make_unique<frc::Encoder> ( ENCODER_DRIVE_RIGHT_A, ENCODER_DRIVE_RIGHT_B );

    LeftEncoder->SetReverseDirection ( true );
    RightEncoder->SetReverseDirection ( true );

    LeftEncoder->SetDistancePerPulse ( ENCODER_DISTANCE_PER_PULSE );
    RightEncoder->SetDistancePerPulse ( ENCODER_DISTANCE_PER_PULSE );

    LeftOutput = std::make_unique<PIDOutputReceiver> ();
    RightOutput = std::make_unique<PIDOutputReceiver> ();
    LeftPID = std::make_unique<frc::PIDController> ( PID_LEFT_P, PID_LEFT_I, PID_LEFT_D, PID_LEFT_F, LeftEncoder.get(), LeftOutput.get() );
    RightPID = std::make_unique<frc::PIDController> ( PID_RIGHT_P, PID_RIGHT_I, PID_RIGHT_D, PID_RIGHT_F, RightEncoder.get(), RightOutput.get() );

    TurnOutput = std::make_unique<PIDOutputReceiver> ();
    TurnPID = std::make_unique<frc::PIDController> ( PID_TURN_P, PID_TURN_I, PID_TURN_D, PID_TURN_F, ahrs.get(), TurnOutput.get() );

    LeftPID->SetContinuous ( false );
    RightPID->SetContinuous ( false );

    LeftPID->SetAbsoluteTolerance ( PID_LEFT_TOLERANCE );
    RightPID->SetAbsoluteTolerance ( PID_RIGHT_TOLERANCE );

    TurnPID->SetContinuous ( true );
    TurnPID->SetInputRange ( -180.0, 180.0 );
    TurnPID->SetOutputRange ( -1.0, 1.0 );
    TurnPID->SetAbsoluteTolerance ( PID_TURN_TOLERANCE );
    LiveWindow::GetInstance()->AddActuator ( "Drivetrain", "TurnPID", TurnPID.get() );
    LiveWindow::GetInstance()->AddActuator ( "Drivetrain", "LeftPID", LeftPID.get() );
    LiveWindow::GetInstance()->AddActuator ( "Drivetrain", "RightPID", RightPID.get() );
    LiveWindow::GetInstance()->AddSensor ( "Drivetrain", "Gyro", ahrs.get() );
    LiveWindow::GetInstance()->AddSensor ( "Drivetrain", "LeftEncoder", LeftEncoder.get() );
    LiveWindow::GetInstance()->AddSensor ( "Drivetrain", "RightEncoder", RightEncoder.get() );

    CardinalDash::Dashboard::Subscribe ( std::string ( "subsystems/drivetrain/leftEncoder" ), &GetEncoderValue, LeftEncoder.get() );
    CardinalDash::Dashboard::Subscribe ( std::string ( "subsystems/drivetrain/rightEncoder" ), &GetEncoderValue, RightEncoder.get() );
}

void Drivetrain::InitDefaultCommand()
{
    SetDefaultCommand ( new TeleopDrive() );
}

void Drivetrain::SetRaw ( double left, double right, bool currentLimit )
{
    if ( currentLimit ) {
        SetLeftRaw ( left );
        SetRightRaw ( right );
    } else {
        LeftVictor->Set ( left );
        RightVictor->Set ( right );
    }
}

void Drivetrain::Set ( double left, double right )
{
    LeftPID->SetSetpoint ( left );
    RightPID->SetSetpoint ( right );
}

void Drivetrain::SetAdd ( double left, double right )
{
    LeftPID->SetSetpoint ( LeftPID->GetSetpoint() + left );
    RightPID->SetSetpoint ( RightPID->GetSetpoint() + right );
}

void Drivetrain::SetLeftRaw ( double left )
{
    double voltage = pdp->GetVoltage();
    double maxDiff = MAX_ACCEL * voltage;

    if ( fabs ( left ) - fabs ( lastLeft ) > maxDiff ) {
        if ( lastLeft > left ) {
            if ( lastLeft < 0 && lastLeftGhost > 0 ) {
                left = lastLeftGhost - maxDiff;
            } else {
                left = lastLeft - maxDiff;
            }
        } else {
            if ( lastLeft > 0 && lastLeftGhost < 0 ) {
                left = lastLeftGhost + maxDiff;
            } else {
                left = lastLeft + maxDiff;
            }
        }
    }
    if ( lastLeftGhost > lastLeft ) {
        lastLeftGhost -= MAX_GHOST_ACCEL;
        if ( lastLeftGhost > lastLeft ) {
            lastLeftGhost = lastLeft;
        }
    } else {
        lastLeftGhost += MAX_GHOST_ACCEL;
        if ( lastLeftGhost < lastLeft ) {
            lastLeftGhost = lastLeft;
        }
    }

    double leftTotal = pdp->GetCurrent ( 0 ) + pdp->GetCurrent ( 1 ) + pdp->GetCurrent ( 2 );

    if ( leftTotal > 100 ) {
        left /= ( 100/leftTotal );
    }

    if ( voltage < 10 ) {
        left /= ( 10/voltage );
    }

    LeftVictor->Set ( left );

    lastLeft = left;
}

void Drivetrain::SetRightRaw ( double right )
{
    double voltage = pdp->GetVoltage();
    double maxDiff = MAX_ACCEL * voltage;

    if ( fabs ( right )- fabs ( lastRight ) > maxDiff ) {
        if ( lastRight > right ) {
            if ( lastRight < 0 && lastRightGhost > 0 ) {
                right = lastRightGhost - maxDiff;
            } else {
                right = lastRight - maxDiff;
            }
        } else {
            if ( lastRight > 0 && lastRightGhost < 0 ) {
                right = lastRightGhost + maxDiff;
            } else {
                right = lastRight + maxDiff;
            }
        }
    }
    if ( lastRightGhost > lastRight ) {
        lastRightGhost -= MAX_GHOST_ACCEL;
        if ( lastRightGhost > lastRight ) {
            lastRightGhost = lastRight;
        }
    } else if ( lastRightGhost < lastRight ) {
        lastRightGhost += MAX_GHOST_ACCEL;
        if ( lastRightGhost < lastRight ) {
            lastRightGhost = lastRight;
        }
    }

    double rightTotal = pdp->GetCurrent ( 13 ) + pdp->GetCurrent ( 14 ) + pdp->GetCurrent ( 15 );

    if ( rightTotal > 100 ) {
        right /= ( 100/rightTotal );
    }

    if ( voltage < 10 ) {
        right /= ( 10/voltage );
    }

    RightVictor->Set ( right );

    lastRight = right;
}

void Drivetrain::Shift ( bool high )
{
    LeftSolenoid->Set ( high ? frc::DoubleSolenoid::Value::kForward :
                        frc::DoubleSolenoid::Value::kReverse );
    RightSolenoid->Set ( high ? frc::DoubleSolenoid::Value::kForward :
                         frc::DoubleSolenoid::Value::kReverse );
}

void Drivetrain::EnablePID()
{
    LeftPID->Reset();
    RightPID->Reset();
    LeftPID->Enable();
    RightPID->Enable();

    LeftEncoder->Reset();
    RightEncoder->Reset();
}

void Drivetrain::DisablePID()
{
    LeftPID->Disable();
    RightPID->Disable();

    LeftEncoder->Reset();
    RightEncoder->Reset();

    lastLeft = 0;
    lastRight = 0;
}

bool Drivetrain::DistancePIDDone()
{
    return LeftPID->OnTarget();
}

double Drivetrain::GetLeftPIDOutput()
{
    return LeftOutput->GetValue();
}

double Drivetrain::GetRightPIDOutput()
{
    return RightOutput->GetValue();
}

double Drivetrain::GetEncoderValue ( void* instance )
{
    return ( ( Encoder* ) instance )->Get();
}

double Drivetrain::GetAngle ()
{
    return ahrs->GetYaw();
}

void Drivetrain::ResetAngle ()
{
    ahrs->Reset();
}

void Drivetrain::EnableTurnPID()
{
    TurnPID->Reset();
    TurnPID->Enable();
}

void Drivetrain::DisableTurnPID()
{
    TurnPID->Disable();
}
void Drivetrain::SetTurnAngle ( double value )
{
    TurnPID->SetSetpoint ( value );
}

double Drivetrain::GetTurnPIDOutput ()
{
    return TurnOutput->GetValue();
}

bool Drivetrain::GetTurnDone ()
{
    return TurnPID->OnTarget();
}

double Drivetrain::GetTurnPIDError ()
{
    return TurnPID->GetError();
}

double Drivetrain::GetLeftEncoderDistance()
{
    return LeftEncoder->GetDistance();
}

double Drivetrain::GetRightEncoderDistance()
{
    return RightEncoder->GetDistance();
}
