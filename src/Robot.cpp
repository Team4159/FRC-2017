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

class Robot: public CardinalDash::IterativeRobot {
public:
    static void term(int signum)
    {
        CardinalDash::Server::Term();
    }

	void RobotInit() override {
        struct sigaction action;
        memset(&action, 0, sizeof(struct sigaction));
        action.sa_handler = (void(*)(int))term;
        sigaction(SIGTERM, &action, NULL);

        IterativeRobot::RobotInit();

        CommandBase::Init();
	}

    void RobotPeriodic() override {
        IterativeRobot::RobotPeriodic();
    }

	void DisabledInit() override {
        IterativeRobot::DisabledInit();
	}

	void DisabledPeriodic() override {
        IterativeRobot::DisabledPeriodic();

		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit() override {
        IterativeRobot::AutonomousInit();
	}

	void AutonomousPeriodic() override {
        IterativeRobot::AutonomousPeriodic();

		Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
        IterativeRobot::TeleopInit();

	}

	void TeleopPeriodic() override {
        IterativeRobot::TeleopPeriodic();

		Scheduler::GetInstance()->Run();
	}

	void TestPeriodic() override {
        IterativeRobot::TestPeriodic();

		LiveWindow::GetInstance()->Run();
	}

private:
	//std::unique_ptr<Command> autonomousCommand;
	//SendableChooser<Command*> chooser;
};

START_ROBOT_CLASS(Robot)
