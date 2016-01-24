#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
//Constant Ratios
	const int RATIO_WINCHMOTORENCODERTICKSTOREV = 497;

//DIO Ports
	//prefix DIO_

//Motors
	const int PORT_LEFTMOTOR = 0;
	const int PORT_RIGHTMOTOR = 1;
	const int PORT_SHOOTERMOTOR = 2;
	const int PORT_INTAKEMOTOR= 3;

//Pnuematics Ports
	const int PNM_COMPRESSOR = 0;
	const int PNM_SHOOTERLOCK = 1;
	const int PNM_INTAKEACTUATE = 2;

//Buttons and Axes

	//Shooter
	const int BTN_PRESET_A = 0;
	const int BTN_PRESET_B = 3;



	//Intake
	const int BTN_INTAKE = 1;
	const int BTN_OUTAKE = 2;
	const int BTN_ACTUATE = 5;

#endif
