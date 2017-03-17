#include "Gyrosensor.h"
#include "../RobotMap.h"

Gyrosensor::Gyrosensor() : Subsystem("ExampleSubsystem") {
    g = std::make_unique<frc::AnalogGyro> (GYRO_PORT);
}

double Gyrosensor::GetAngle() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	return g->GetAngle();
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
