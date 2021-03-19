#ifndef _AUTO_FUNCTIONS_HPP_
#define _AUTO_FUNCTIONS_HPP_

// Simple Auto Functions

void simple_drive(double target, double kp, double max_time);

void simple_turn(double target, double kp, double max_time);

// Complex Auto Functions

#define MINIMUM_DRIVE_POWER 10
#define MINIMUM_ACCEL_POWER 50

void complex_drive(double target, double max, double akp, double dkp, double max_time);

void complex_turn(double target, double max, double akp, double dkp, double max_time);

#endif
