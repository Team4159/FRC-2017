#include "IterativeRobot.h"

#include <iostream>

#include "Dashboard.h"

namespace CardinalDash
{
    IterativeRobot::IterativeRobot() : frc::IterativeRobot()
    {

    };

    void IterativeRobot::RobotInit()
    {
        CardinalDash::Dashboard::Init();
    }

    void IterativeRobot::DisabledInit()
    {

    }

    void IterativeRobot::AutonomousInit()
    {

    }

    void IterativeRobot::TeleopInit()
    {

    }

    void IterativeRobot::TestInit()
    {

    }

    void IterativeRobot::RobotPeriodic()
    {

    }

    void IterativeRobot::DisabledPeriodic()
    {
        CardinalDash::Dashboard::PushValues();
    }

    void IterativeRobot::AutonomousPeriodic()
    {
        CardinalDash::Dashboard::PushValues();
    }

    void IterativeRobot::TeleopPeriodic()
    {
        CardinalDash::Dashboard::PushValues();
    }

    void IterativeRobot::TestPeriodic()
    {
        CardinalDash::Dashboard::PushValues();
    }

}
