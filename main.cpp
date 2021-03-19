#include "main.h"

Motor DriveLF(1);
Motor DriveLB(2);
Motor DriveRF(3);
Motor DriveRB(4);
Motor IntakeL(5);
Motor IntakeR(6);
Motor Outake(7);
Motor Indexer(8);

Imu gyro(9);
Controller master(E_CONTROLLER_MASTER);


void initialize() {
	lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	
}

void opcontrol() {
	while (true) {
		delay(20);
	}
}
