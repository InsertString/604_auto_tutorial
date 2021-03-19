#include "main.h"

/*
  minimal function to move the robot to the target encoder amount
*/
void simple_drive(double target, double kp, double max_time) {
  // reset the sensors
  reset_auto_sensors();
  // declare all the variables
  double error = target - leftDrivePosition();
  bool complete = false;
  Timer exit_timer;
  Timer timeout_timer;
  // start the timers
  exit_timer.reset();
  timeout_timer.reset();
  // loop as long as the robot is not at the target position
  while (complete == false) {
    // calculate the error and power the drive based on the error
    error = target - leftDrivePosition();
    power_drive(error * kp, 0);

    // check if the robot has reached the target position
    if (fabs(error) < 10) {
      // check if the robot has been at the target position for 300 ms
      if (exit_timer.delta_time() > 300)
        complete = true;
    }
    else
      exit_timer.reset();

    // check if the function has been running too long
    if (timeout_timer.delta_time() > max_time)
      complete = true;
  }
  // stop the drive motors at the end
  power_drive(0, 0);
}

/*
  minimal function to turn the robot to the target imu rotation
*/
void simple_turn(double target, double kp, double max_time) {
  // reset the sensors
  reset_auto_sensors();
  // declare all the variables
  double error = target - gyro.get_rotation();
  bool complete = false;
  Timer exit_timer;
  Timer timeout_timer;
  // start the timers
  exit_timer.reset();
  timeout_timer.reset();
  // loop as long as the robot is not at the target position
  while (complete == false) {
    // calculate the error and power the drive based on the error
    error = target - gyro.get_rotation();
    power_drive(0, error * kp);

    // check if the robot has reached the target position
    if (fabs(error) < 1) {
      // check if the robot has been at the target position for 300 ms
      if (exit_timer.delta_time() > 300)
        complete = true;
    }
    else
      exit_timer.reset();

    // check if the function has been running too long
    if (timeout_timer.delta_time() > max_time)
      complete = true;
  }
  // stop the drive motors at the end
  power_drive(0, 0);
}

/*
  a more consistent function to drive the robot to the target encoder amount
  this function has several features:
    - centered drive position rather than relying on one side
    - angle correction to ensure a straight path
    - acceleration deceleration to increase consistency
    - accounts for the minimum power needed to move the robot
    - max speed filtering
*/
void complex_drive(double target, double max, double akp, double dkp, double max_time) {
  // reset the sensors
  reset_auto_sensors();
  // declare all the variables
  double error = target - centeredDrivePosition();
  double gyro_error = 0 - gyro.get_rotation();
  bool complete = false;
  Timer exit_timer;
  Timer timeout_timer;
  int direction = (target > 0) ? 1 : -1;
  double power = 0;
  // start the timers
  exit_timer.reset();
  timeout_timer.reset();
  // loop as long as the robot is not at the target position
  while (complete == false) {
    // calculate the error
    error = target - centeredDrivePosition();
    gyro_error = 0 - gyro.get_rotation();

    // check if we have reached the halfway point
    if (fabs(error) > fabs(target / 2)) {
      // if we are before the half way point we need to accelerate
      power = (MINIMUM_ACCEL_POWER * direction) + (centeredDrivePosition() * akp);
    }
    else {
      // if we are after the halfway point we need to decelerate
      power = (MINIMUM_DRIVE_POWER * direction) + (error * dkp);
    }

    // filter the power so that its not higher then the max
    if (power > max) power = max;
    else if (power < -max) power = -max;

    power_drive(power, gyro_error);

    // check if the robot has reached the target position
    if (fabs(error) < 10) {
      // check if the robot has been at the target position for 300 ms
      if (exit_timer.delta_time() > 300)
        complete = true;
    }
    else
      exit_timer.reset();

    // check if the function has been running too long
    if (timeout_timer.delta_time() > max_time)
      complete = true;
  }
  // stop the drive motors at the end
  power_drive(0, 0);
}

/*
  a more consistent function to drive the robot to the target encoder amount
  this function has several features:
    - acceleration deceleration to increase consistency
    - accounts for the minimum power needed to move the robot
    - max speed filtering
*/
void complex_turn(double target, double max, double akp, double dkp, double max_time) {
  // reset the sensors
  reset_auto_sensors();
  // declare all the variables
  double error = target - gyro.get_rotation();
  bool complete = false;
  Timer exit_timer;
  Timer timeout_timer;
  int direction = (target > 0) ? 1 : -1;
  double power = 0;
  // start the timers
  exit_timer.reset();
  timeout_timer.reset();
  // loop as long as the robot is not at the target position
  while (complete == false) {
    // calculate the error
    error = target - gyro.get_rotation();

    // check if we have reached the halfway point
    if (fabs(error) > fabs(target / 2)) {
      // if we are before the half way point we need to accelerate
      power = (MINIMUM_ACCEL_POWER * direction) + (gyro.get_rotation() * akp);
    }
    else {
      // if we are after the halfway point we need to decelerate
      power = (MINIMUM_DRIVE_POWER * direction) + (error * dkp);
    }

    // filter the power so that its not higher then the max
    if (power > max) power = max;
    else if (power < -max) power = -max;

    power_drive(0, power);

    // check if the robot has reached the target position
    if (fabs(error) < 10) {
      // check if the robot has been at the target position for 300 ms
      if (exit_timer.delta_time() > 300)
        complete = true;
    }
    else
      exit_timer.reset();

    // check if the function has been running too long
    if (timeout_timer.delta_time() > max_time)
      complete = true;
  }
  // stop the drive motors at the end
  power_drive(0, 0);
}
