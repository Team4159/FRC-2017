#ifndef CARDINAL_DASH_ITERATIVE_ROBOT_H
#define CARDINAL_DASH_ITERATIVE_ROBOT_H

#include <IterativeRobot.h>

namespace CardinalDash
{
    class IterativeRobot : public frc::IterativeRobot
    {
        public:
            IterativeRobot();
            virtual void RobotInit();
            virtual void DisabledInit();
            virtual void AutonomousInit();
            virtual void TeleopInit();
            virtual void TestInit();

            virtual void RobotPeriodic();
            virtual void DisabledPeriodic();
            virtual void AutonomousPeriodic();
            virtual void TeleopPeriodic();
            virtual void TestPeriodic();
        private:
    };
}

#endif // CARDINAL_DASH_ITERATIVE_ROBOT_H
