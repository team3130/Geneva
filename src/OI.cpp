#include "OI.h"
#include "RobotMap.h"
#include "Commands/ReloadCatapult.h"
#include "Commands/Pintake.h"
#include "Commands/CameraAim.h"
#include "Commands/ControlCatapultFire.h"
#include "Commands/DriveShiftUp.h"
#include "Commands/DriveShiftDown.h"
#include "Commands/DriveStreightTest.h"

OI* OI::m_pInstance = NULL;

OI::OI()
{
	// Process operator interface input here.
	stickL = new Joystick(0);
	stickR = new Joystick(1);
	gamepad = new Joystick(2);

	preset1 	= new JoystickButton(gamepad, BTN_PRESET_1);
	preset2 	= new JoystickButton(gamepad, BTN_PRESET_2);
	intakePin 	= new JoystickButton(gamepad, BTN_INTAKEPIN);
	aimLeft 	= new JoystickButton(stickR, BTN_AIMLEFT);
	aimRight	= new JoystickButton(stickR, BTN_AIMRIGHT);
	fire    	= new JoystickButton(gamepad, BTN_SHOOT);
	shiftDown  	= new JoystickButton(stickL, BTN_SHIFT);
	shiftUp		= new JoystickButton(stickR, BTN_SHIFT);
	streight	= new JoystickButton(stickR, 10);

	preset1->WhenPressed(new ReloadCatapult(BTN_PRESET_1));
	preset2->WhenPressed(new ReloadCatapult(BTN_PRESET_2));
	intakePin->ToggleWhenPressed(new Pintake());
	aimLeft->WhileHeld(new CameraAim(CameraAim::kLeft));
	aimRight->WhileHeld(new CameraAim(CameraAim::kRight));
	fire->WhileHeld(new ControlCatapultFire());
	shiftUp->WhenPressed(new DriveShiftUp());
	shiftDown->WhenPressed(new DriveShiftDown());
	streight->WhileHeld(new DriveStreightTest());

	//SMD Input for Auton
	//Creates Radio Buttons for selection of Auton positions	//TODO:Determine the correct angles for this
	positionChooser = new SendableChooser();
	positionChooser->AddDefault("Low Bar",new double(Preferences::GetInstance()->GetDouble("Auton Turn Angle LowBar", -45)));
	positionChooser->AddObject("Position 2", new double(Preferences::GetInstance()->GetDouble("Auton Turn Angle Position2",-25)));
	positionChooser->AddObject("Position 3", new double(Preferences::GetInstance()->GetDouble("Auton Turn Angle Position3",0)));
	positionChooser->AddObject("Position 4", new double(Preferences::GetInstance()->GetDouble("Auton Turn Angle Position4",0)));
	positionChooser->AddObject("position 5", new double(Preferences::GetInstance()->GetDouble("Auton Turn Angle Position5",25)));
	SmartDashboard::PutData("Auton Position",positionChooser);
}

OI* OI::GetInstance()
{
	if(!m_pInstance) m_pInstance = new OI;
	return m_pInstance;
}
