#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include <WPILib.h>
#define _USE_MATH_DEFINES
#include <math.h>

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
//Constant Ratios
	const int RATIO_WINCHCODESPERREV = 1024;
	const int RATIO_DRIVECODESPERREV = 360;

//DIO Ports
	// Prefix DIO_

//Motors-PWM
	const int PORT_CLIMBERTAPE = 0;
	const int PORT_CLIMBERWINCH = 1;
	const int PORT_CLIMBERWINCH2 = 2;

//Motors-CAN
	const int CAN_PNMMODULE = 1;
	const int CAN_SHOOTERMOTOR = 2;
	const int CAN_LEFTMOTORFRONT = 3;
	const int CAN_LEFTMOTORREAR = 4;
	const int CAN_RIGHTMOTORFRONT = 5;
	const int CAN_RIGHTMOTORREAR = 6;
	const int CAN_INTAKEMOTOR = 7;
	const int CAN_CLIMBERTAPE = 8;
	const int CAN_CLIMBERWINCH = 9;
	const int CAN_CLIMBERWINCH2 = 10;

//Pnuematics Ports
	const int PNM_INTAKEPIN = 0;
	const int PNM_SHOOTERLOCK = 1;
	const int PNM_GEARSHIFTER = 2;
	const int PNM_INTAKEACTUATEOUT = 3;
	const int PNM_INTAKEACTUATEUP = 4;

//Analog Input
	//Prefix ANG_

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

	//POV Degress
	const int LST_POV_UNPRESSED = -1;
	const int LST_POV_N = 0;
	const int LST_POV_NE = 45;
	const int LST_POV_E = 90;
	const int LST_POV_SE = 135;
	const int LST_POV_S = 180;
	const int LST_POV_SW = 225;
	const int LST_POV_W = 270;
	const int LST_POV_NW = 315;


	//Catapult
	const int BTN_PRESET_1 = LST_BTN_X;
	const int BTN_PRESET_2 = LST_BTN_Y;
	const int BTN_SHOOT = LST_BTN_RBUMPER;
	const int AXS_WINCH = LST_AXS_RJOYSTICKY;

	//Climber
	const int AXS_CLIMBERTAPES = LST_AXS_LJOYSTICKY;
	const int POV_CLIMBERWINCHDOWN  = LST_POV_S; //POV DOWN

	//Intake
	const int BTN_INTAKE = LST_BTN_A;
	const int BTN_OUTAKE = LST_BTN_B;
	const int BTN_INTAKEVERTICAL = LST_BTN_LBUMPER;
	const int AXS_INTAKEHORIZONTAL = LST_AXS_LTRIGGER;
	const int BTN_INTAKEPIN = LST_BTN_BACK;

	const int POV_CDFMODE = LST_POV_S;
	const int POV_PORTCULLISMODE = LST_POV_W;
	const int POV_INTAKEIN = LST_POV_N;
	const int POV_INTAKEOUT = LST_POV_E;

	//Defenses
	const int AXS_DEFENSEACTUATER = LST_AXS_RTRIGGER;

	//Vision
	const int BTN_AIMLEFT = 3;
	const int BTN_AIMRIGHT = 4;

	//Drive
	const int BTN_SHIFT = 1;
#endif
