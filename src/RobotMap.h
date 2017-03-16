#ifndef ROBOTMAP_H
#define ROBOTMAP_H

// Motor ports
const int MOTOR_LEFT_DRIVE = 0;
const int MOTOR_RIGHT_DRIVE = 1;
const int MOTOR_CLIMBER = 2;
const int MOTOR_INTAKE = 3;

// Solenoid ports for shifting
const int SOLENOID_SHIFTER_LEFT_A = 0;
const int SOLENOID_SHIFTER_LEFT_B = 1;
const int SOLENOID_SHIFTER_RIGHT_A = 2;
const int SOLENOID_SHIFTER_RIGHT_B = 3;

// Solenoid ports for lifter
const int SOLENOID_LIFTER_LEFT_A = 4;
const int SOLENOID_LIFTER_LEFT_B = 5;
const int SOLENOID_LIFTER_RIGHT_A = 6;
const int SOLENOID_LIFTER_RIGHT_B = 7;

// Solenoid ports for gripper
const int SOLENOID_GRIPPER_A = 0;
const int SOLENOID_GRIPPER_B = 1;

// Encoder port for drivetrain
const int ENCODER_DRIVE_LEFT_A = 0;
const int ENCODER_DRIVE_LEFT_B = 1;
const int ENCODER_DRIVE_RIGHT_A = 2;
const int ENCODER_DRIVE_RIGHT_B = 3;

#endif  // ROBOTMAP_H
