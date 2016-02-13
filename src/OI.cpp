#include "OI.h"
#include "RobotMap.h"
#include "Commands/ReloadCatapult.h"
#include "Commands/PinchBall.h"
#include "Commands/CameraAim.h"

OI* OI::m_pInstance = NULL;

OI::OI()
{
	// Process operator interface input here.
	stickL = new Joystick(0);
	stickR = new Joystick(1);
	gamepad = new Joystick(2);
	preset1 = new JoystickButton(gamepad, BTN_PRESET_1);
	preset2 = new JoystickButton(gamepad, BTN_PRESET_2);
	bincher = new JoystickButton(gamepad, BTN_BINCHER);
	preset1->WhenPressed(new ReloadCatapult(BTN_PRESET_1));
	preset2->WhenPressed(new ReloadCatapult(BTN_PRESET_2));
	bincher->ToggleWhenPressed(new PinchBall());
	aimLeft = new JoystickButton(stickR, BTN_AIMLEFT);
	aimLeft->WhileHeld(new CameraAim(CameraAim::kLeft));
	aimRight = new JoystickButton(stickR, BTN_AIMRIGHT);
	aimRight->WhileHeld(new CameraAim(CameraAim::kRight));
}

OI* OI::GetInstance()
{
	if(!m_pInstance) m_pInstance = new OI;
	return m_pInstance;
}
