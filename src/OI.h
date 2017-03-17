#ifndef OI_H
#define OI_H

#include <Joystick.h>

class OI
{
    public:
        OI();
        double GetLeftJoystick();
        double GetRightJoystick();
        double GetIntake();
        bool GetLifter();
        bool GetShift();
        bool GetGripper();

    private:
        std::unique_ptr<frc::Joystick> leftStick;
        std::unique_ptr<frc::Joystick> rightStick;
        std::unique_ptr<frc::Joystick> secondaryStick;

        bool lifterPosition = false; // down
        bool shifterPosition = false; // Low gear
};

#endif  // OI_H
