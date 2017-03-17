#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <memory>
#include <string>

#include "CardinalDash/Command.h"

#include "OI.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/GearBox.h"

class CommandBase: public CardinalDash::Command
{
    public:
        CommandBase ( const std::string& name );
        CommandBase() = default;

        static void Init();

        // Create a single static instance of all of your subsystems
        static std::unique_ptr<Drivetrain> drivetrain;
        static std::unique_ptr<GearBox> gearBox;
        static std::unique_ptr<OI> oi;
        static std::unique_ptr<Gyrosensor> gyro;

};

#endif  // COMMAND_BASE_H
