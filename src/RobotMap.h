#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

//Drive Motors
	const int LEFTBACKMOTOR = 0;
	const int RIGHTBACKMOTOR = 1;
	const int LEFTFRONTMOTOR = 2;
	const int RIGHTFRONTMOTOR = 3;
//Intake Motors
	const int INTAKEMOTOR = 4;
//Shooter Motors
	const int SHOOTERMOTOR = 5;
#endif
