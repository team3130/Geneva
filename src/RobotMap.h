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
	const uint8_t PNM_MODULE = 1;
	const int PNM_COMPRESSOR = 0;
	const int PNM_SHOOTERLOCK = 1;
	const int PNM_INTAKEACTUATE = 2;

//Buttons and Axes


	//Button List
	const int LST_BTN_A = 1;
	const int LST_BTN_B = 2;
	const int LST_BTN_X = 3;
	const int LST_BTN_Y = 4;
	const int LST_BTN_LBUMPER = 5;
	const int LST_BTN_RBUMPER = 6;
	const int LST_BTN_BACK = 7;
	const int LST_BTN_START = 8;
	const int LST_BTN_RJOYSTICKPRESS = 9;
	const int LST_BTN_LJOYSTICKPRESS = 10;

	//Axis List
	const int LST_AXS_LJOYSTICKX = 0;
	const int LST_AXS_LJOYSTICKY = 1;
	const int LST_AXS_LTRIGGER = 2;
	const int LST_AXS_RTRIGGER = 3;
	const int LST_AXS_RJOYSTICKX = 4;
	const int LST_AXS_RJOYSTICKY = 5;

	//Shooter
	const int BTN_PRESET_A = 0;
	const int BTN_PRESET_B = 3;
	const uint32_t BTN_SHOOT = 5;

	//Winch
	const uint32_t AXS_WINCH = 1;

	//Intake
	const int BTN_INTAKE = 1;
	const int BTN_OUTAKE = 2;
	const uint32_t BTN_GRAB = 3;

#endif
