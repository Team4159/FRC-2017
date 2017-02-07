#include "CommandBase.h"

#include <Commands/Scheduler.h>

#include "Subsystems/Drivetrain.h"
#include "Subsystems/GearBox.h"

std::unique_ptr<Drivetrain> CommandBase::drivetrain = NULL;
std::unique_ptr<GearBox> CommandBase::gearBox = NULL;
std::unique_ptr<OI> CommandBase::oi = NULL;

CommandBase::CommandBase ( const std::string& name ) : CardinalDash::Command (
        name )
{

}

void CommandBase::Init()
{
    CommandBase::drivetrain = std::make_unique<Drivetrain>();
    CommandBase::gearBox = std::make_unique<GearBox>();
    CommandBase::oi = std::make_unique<OI>();
}
