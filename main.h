#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_
#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "base_function.hpp"
#include "auto_functions.hpp"
#include "auto_code.hpp"
#include "timer.hpp"

using namespace pros;
// using namespace pros::literals;
// using namespace okapi;

#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#endif

extern Motor DriveLF;
extern Motor DriveLB;
extern Motor DriveRF;
extern Motor DriveRB;
extern Motor IntakeL;
extern Motor IntakeR;
extern Motor Outake;
extern Motor Indexer;
extern Imu gyro;
extern Controller master;

#endif  // _PROS_MAIN_H_
