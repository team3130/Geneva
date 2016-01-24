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
	const int DIO_SHOOTERLIMITLOWER = 0;
	const int DIO_SHOOTERENCODERA = 1;
	const int DIO_SHOOTERENCODERB = 2;

//Motors
	const int PORT_LEFTMOTOR = 0;
	const int PORT_RIGHTMOTOR = 1;
	const int PORT_SHOOTERMOTOR = 2;
	const int PORT_INTAKEMOTOR= 3;

//Pnuematics Ports
	const int PNM_COMPRESSOR = 0;
	const int PNM_SHOOTERLOCK = 1;
	const int PNM_INTAKEACTUATE = 2;
#endif
