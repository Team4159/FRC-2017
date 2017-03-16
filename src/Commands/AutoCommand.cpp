#include "AutoCommand.h"

#include "CommandBase.h"

AutoCommand::AutoCommand() : CommandBase ( "AutoCommand" )
{
    Requires ( CommandBase::drivetrain.get() );
    Requires ( CommandBase::gearBox.get() );
}

void AutoCommand::Initialize()
{
    CommandBase::drivetrain->EnablePID();
    CommandBase::drivetrain->Set ( 10, 10 );
}

void AutoCommand::Execute()
{

}

bool AutoCommand::IsFinished()
{
    return false;
}

void AutoCommand::End()
{
    CommandBase::drivetrain->DisablePID();
}

void AutoCommand::Interrupted()
{

}
