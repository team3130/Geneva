#include "OI.h"
#include "RobotMap.h"
#include "Commands/ReloadCatapult.h"

OI* OI::m_pInstance = NULL;

OI::OI()
{
	// Process operator interface input here.
	stickL = new Joystick(0);
	stickR = new Joystick(1);
	gamepad = new Joystick(2);
	preset1 = new JoystickButton(gamepad, BTN_PRESET_1);
	preset2 = new JoystickButton(gamepad, BTN_PRESET_2);
	preset1->WhenPressed(new ReloadCatapult(BTN_PRESET_1));
	preset2->WhenPressed(new ReloadCatapult(BTN_PRESET_2));
}

OI* OI::GetInstance()
{
	if(!m_pInstance) m_pInstance = new OI;
	return m_pInstance;
}
