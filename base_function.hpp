#ifndef _BASE_FUNCTION_HPP_
#define _BASE_FUNCTION_HPP_

void power_drive(double power, double turn);

void power_intake(double power);

void power_indexer(double power);

void power_shooter(double power);

double leftDrivePosition();

double rightDrivePosition();

double centeredDrivePosition();

void reset_auto_sensors();

#endif
