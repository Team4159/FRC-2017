#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <memory>
#include <string>

#include "CardinalDash/Command.h"

#include "OI.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/GearBox.h"
#include "Subsystems/Climber.h"

class CommandBase: public CardinalDash::Command
{
    public:
        CommandBase ( const std::string& name );
        CommandBase() = default;

        static void Init();

        static void Enable();
        static void Disable();

        // Create a single static instance of all of your subsystems
        static std::unique_ptr<Drivetrain> drivetrain;
        static std::unique_ptr<GearBox> gearBox;
        static std::unique_ptr<Climber> climber;
        static std::unique_ptr<OI> oi;
};

#endif  // COMMAND_BASE_H
