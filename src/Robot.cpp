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
#include "Commands/AutoCommand.h"

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

    autonomousCommand = std::make_unique<AutoCommand> ( false );

    if ( autonomousCommand.get() != nullptr ) {
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
}

void Robot::TeleopPeriodic()
{
    super::TeleopPeriodic();

    Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic()
{
    super::TestPeriodic();

    LiveWindow::GetInstance()->Run();
}

START_ROBOT_CLASS ( Robot )
