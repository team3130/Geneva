#include "OI.h"
#include "RobotMap.h"
#include "Commands/ReloadCatapult.h"
#include "Commands/Pintake.h"
#include "Commands/CameraAim.h"
#include "Commands/ControlCatapultFire.h"
#include "Commands/DriveShift.h"
#include "Commands/DriveStreightTest.h"

OI* OI::m_pInstance = NULL;

OI::OI()
{
	// Process operator interface input here.

//	stickL = new Joystick(0);
//	stickR = new Joystick(1);
//	gamepad = new Joystick(2);

	gamepad1 = new Joystick(0);
	gamepad = new Joystick(1);

	preset1 	= new JoystickButton(gamepad, BTN_PRESET_1);
	preset2 	= new JoystickButton(gamepad, BTN_PRESET_2);
	intakePin 	= new JoystickButton(gamepad, BTN_INTAKEPIN);
	aimLeft 	= new JoystickButton(gamepad1, BTN_AIMLEFT);
	aimRight	= new JoystickButton(gamepad1, BTN_AIMRIGHT);
	fire    	= new JoystickButton(gamepad, BTN_SHOOT);
	shift   	= new JoystickButton(gamepad1, BTN_SHIFT);
	streight	= new JoystickButton(gamepad1, 10);

	preset1->WhenPressed(new ReloadCatapult(BTN_PRESET_1));
	preset2->WhenPressed(new ReloadCatapult(BTN_PRESET_2));
	intakePin->ToggleWhenPressed(new Pintake());
	aimLeft->WhileHeld(new CameraAim(CameraAim::kLeft));
	aimRight->WhileHeld(new CameraAim(CameraAim::kRight));
	fire->WhileHeld(new ControlCatapultFire());
	shift->ToggleWhenPressed(new DriveShift());
	streight->WhileHeld(new DriveStreightTest());
}

OI* OI::GetInstance()
{
	if(!m_pInstance) m_pInstance = new OI;
	return m_pInstance;
}
