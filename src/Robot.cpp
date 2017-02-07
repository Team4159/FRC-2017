#include "Robot.h"

#include <memory>
#include <signal.h>
#include <iostream>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "CommandBase.h"

#include "CardinalDash/IterativeRobot.h"
#include "CardinalDash/Server.h"

void Robot::term ( int signum ) {
    CardinalDash::Server::Term();
}

void Robot::RobotInit() {
    struct sigaction action;
    memset ( &action, 0, sizeof ( struct sigaction ) );
    action.sa_handler = ( void ( * ) ( int ) ) term;
    sigaction ( SIGTERM, &action, NULL );

    IterativeRobot::RobotInit();

    CommandBase::Init();
}

void Robot::RobotPeriodic() {
    IterativeRobot::RobotPeriodic();
}

void Robot::DisabledInit() {
    IterativeRobot::DisabledInit();
}

void Robot::DisabledPeriodic() {
    IterativeRobot::DisabledPeriodic();

    Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
    IterativeRobot::AutonomousInit();
}

void Robot::AutonomousPeriodic() {
    IterativeRobot::AutonomousPeriodic();

    Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
    IterativeRobot::TeleopInit();
}

void Robot::TeleopPeriodic() {
    IterativeRobot::TeleopPeriodic();

    Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
    IterativeRobot::TestPeriodic();

    LiveWindow::GetInstance()->Run();
}

START_ROBOT_CLASS ( Robot )
