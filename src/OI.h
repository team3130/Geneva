#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI
{
private:
	OI();
	OI(OI const&);
	OI& operator=(OI const&);
	static OI* m_pInstance;

public:
	static OI* GetInstance();
	Joystick*	stickL;
	Joystick*	stickR;
	Joystick*	gamepad;
	JoystickButton* preset1;
	JoystickButton* preset2;
	JoystickButton* intakePin;
	JoystickButton*	aimLeft;
	JoystickButton*	aimRight;
	JoystickButton* fire;
	JoystickButton* shiftDown;
	JoystickButton* shiftUp;
	JoystickButton* streight;

	SendableChooser* positionChooser;
	SendableChooser* defenseChooser;
	double ReturnAutonAngle();
	double ReturnAutonDistance();
};

#endif
