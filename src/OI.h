#ifndef OI_H
#define OI_H

// Comment out to use joystick for primary
// #define OI_XBOX_PRIMARY

#include <Joystick.h>

#ifdef OI_XBOX_PRIMARY
#include <XboxController.h>
#endif // OI_XBOX_PRIMARY

class OI
{
    public:
        OI();
        double GetLeftJoystick();
        double GetRightJoystick();
        double GetIntake();
        double GetClimber();
        bool GetLifter();
        bool GetShift();
        bool GetGripper();

    private:
#ifndef OI_XBOX_PRIMARY
        std::unique_ptr<frc::Joystick> leftStick;
        std::unique_ptr<frc::Joystick> rightStick;
#else
        std::unique_ptr<frc::XboxController> primaryController;
#endif // OI_XBOX_PRIMARY
        std::unique_ptr<frc::Joystick> secondaryStick;

        bool lifterPosition = true; // up
        bool shifterPosition = false; // Low gear
};

#endif  // OI_H
