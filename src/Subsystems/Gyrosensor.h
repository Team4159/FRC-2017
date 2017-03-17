#ifndef Gyrosensor_H
#define Gyrosensor_H

#include <Commands/Subsystem.h>

class Gyrosensor : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
    std::unique_ptr<frc::AnalogGyro> g;
public:
	Gyrosensor();
	double GetAngle(); //radians
};

#endif  // Gyrosensor_H
