#include "main.h"

void power_drive(double power, double turn) {
  DriveRF = power + turn;
  DriveRB = power + turn;
  DriveLF = power + turn;
  DriveLB = power + turn;
}

void power_intake(double power) {
  IntakeL = power;
  IntakeR = power;
}

void power_indexer(double power) {
  Indexer = power;
}

void power_shooter(double power) {
  Outake = power;
}

double leftDrivePosition() {
  return DriveLB.get_position();
}

double rightDrivePosition() {
  return DriveRB.get_position();
}

double centeredDrivePosition() {
  double temp = (rightDrivePosition() + (leftDrivePosition() - rightDrivePosition())/2);
  return temp;
}

void reset_auto_sensors() {
  DriveRB.tare_position();
  DriveLB.tare_position();
  gyro.tare_rotation();
}
