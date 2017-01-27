#include "IterativeRobot.h"

#include <iostream>

#include "Dashboard.h"

namespace CardinalDash {
    IterativeRobot::IterativeRobot() : frc::IterativeRobot() {

   };

    void IterativeRobot::RobotInit() {
        CardinalDash::Dashboard::Init();
    }

    void IterativeRobot::DisabledInit() {

    }

    void IterativeRobot::AutonomousInit() {

    }

    void IterativeRobot::TeleopInit() {

    }

    void IterativeRobot::TestInit() {

    }

    void IterativeRobot::RobotPeriodic() {
        CardinalDash::Dashboard::PushValues();
    }

    void IterativeRobot::DisabledPeriodic() {

    }

    void IterativeRobot::AutonomousPeriodic() {

    }

    void IterativeRobot::TeleopPeriodic() {

    }

    void IterativeRobot::TestPeriodic() {

    }

}
