#include "Robot.h"

#include <memory>
#include <signal.h>
#include <iostream>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include <CameraServer.h>

#include "CommandBase.h"
#include "Commands/DriveDistance.h"
#include "Commands/DeliverGear.h"
#include "Commands/TurnToAngle.h"
#include "Commands/AutoGear.h"

#include "CardinalDash/Server.h"

void Robot::term ( int signum )
{
    CardinalDash::Server::Term();
}

void Robot::RobotInit()
{
    struct sigaction action;
    memset ( &action, 0, sizeof ( struct sigaction ) );
    action.sa_handler = ( void ( * ) ( int ) ) term;
    sigaction ( SIGTERM, &action, NULL );

    super::RobotInit();

    cameraServer = frc::CameraServer::GetInstance();

    cameraServer->StartAutomaticCapture();

    CommandBase::Init();
	
	chooser.AddDefault("Center Peg", new AutoGear(0));
	chooser.AddObject("Left Peg", new AutoGear(-1));
	chooser.AddObject("Right Peg", new AutoGear(1));
}

void Robot::RobotPeriodic()
{
    super::RobotPeriodic();
}

void Robot::DisabledInit()
{
    super::DisabledInit();
    CommandBase::Disable();
}

void Robot::DisabledPeriodic()
{
    super::DisabledPeriodic();

    Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit()
{
    super::AutonomousInit();
    CommandBase::Enable();
	CommandBase::drivetrain->ResetAngle();
	
	autonomousCommand = chooser.GetSelected();
    if ( autonomousCommand != nullptr ) {
        autonomousCommand->Start();
    }
}

void Robot::AutonomousPeriodic()
{
    super::AutonomousPeriodic();

    Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit()
{
    super::TeleopInit();
    CommandBase::Enable();

    autoRecorder = std::make_unique<AutoRecorder> ( true );

    if ( autonomousCommand != nullptr ) {
        autonomousCommand->Cancel();
    }

    CommandBase::Enable();
}

void Robot::TeleopPeriodic()
{
    super::TeleopPeriodic();

    if ( CommandBase::oi->GetRecording() && !autoRecorder->IsRunning() ) {
        autoRecorder->Start();
    } else if ( !CommandBase::oi->GetRecording() && autoRecorder->IsRunning() ) {
        autoRecorder->Cancel();
    }

    Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic()
{
    super::TestPeriodic();

    LiveWindow::GetInstance()->Run();
}

START_ROBOT_CLASS ( Robot )
