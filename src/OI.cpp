#include "OI.h"
#include "RobotMap.h"
#include "Commands/ReloadCatapult.h"
#include "Commands/Pintake.h"
#include "Commands/CameraAim.h"
#include "Commands/ControlCatapultFire.h"
#include "Commands/DriveShiftUp.h"
#include "Commands/DriveShiftDown.h"
#include "Commands/DriveStreightTest.h"
#include "Commands/HandleStopPoints.h"
#include "Commands/WipeStopPoints.h"
#include "Commands/TestStopPoints.h"
#include "Commands/CDFActuate.h"
#include "Commands/PortcullisActuate.h"
#include "Commands/IntakeIn.h"
#include "Commands/IntakeOut.h"
#include "Commands/HeadlightsOn.h"
#include "AutonCommands/AutonDriveToPoint.h"
#include "Subsystems/Chassis.h"

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
	toPoint		= new JoystickButton(stickL, 10);
	headlight	= new JoystickButton(stickR, 2);
	CDFIntake	= new POVTrigger(gamepad, POV_CDFMODE);
	inIntake	= new POVTrigger(gamepad, POV_INTAKEIN);
	intakeOut	= new POVTrigger(gamepad, POV_INTAKEOUT);
	portcullisIntake	= new POVTrigger(gamepad, POV_PORTCULLISMODE);

	addPoint	= new HandleStopPoints();
	wipePoints 	= new WipeStopPoints();
	testPoints	= new TestStopPoints();

	driveDistTest = new AutonDriveToPoint(false);
	driveDistTest->SetParam(20.0,0.0,1.0,0.5);

	preset1->WhenPressed(new ReloadCatapult(BTN_PRESET_1));
	preset2->WhenPressed(new ReloadCatapult(BTN_PRESET_2));
	intakePin->WhileHeld(new Pintake());
	aimLeft->WhenPressed(new CameraAim(CameraAim::kLeft, aimLeft));
	aimRight->WhenPressed(new CameraAim(CameraAim::kRight, aimRight));
	fire->WhenPressed(new ControlCatapultFire());
	shiftUp->WhenPressed(new DriveShiftUp());
	shiftDown->WhenPressed(new DriveShiftDown());
	streight->WhileHeld(new DriveStreightTest());
	toPoint->WhileHeld(driveDistTest);
	portcullisIntake->WhileActive(new PortcullisActuate());
	CDFIntake->WhileActive(new CDFActuate());
	inIntake->WhileActive(new IntakeIn());
	intakeOut->WhileActive(new IntakeOut());
	headlight->ToggleWhenPressed(new HeadlightsOn());

	SmartDashboard::PutData("Wipe Stop Data", wipePoints);
	SmartDashboard::PutData("Add Point", addPoint);
	SmartDashboard::PutData("Test Points", testPoints);

	//SMD Input for Auton
	//Creates Radio Buttons for selection of Auton positions
	positionChooser = new SendableChooser();
	positionChooser->AddDefault("Low Bar",new int(1));
	positionChooser->AddObject("Position 2", new int(2));
	positionChooser->AddObject("Position 3", new int(3));
	positionChooser->AddObject("Position 4", new int(4));
	positionChooser->AddObject("position 5", new int(5));
	SmartDashboard::PutData("Auton Position",positionChooser);

	//Creates Radio Buttons for selection of Auton defenses
	defenseChooser = new SendableChooser();
	defenseChooser->AddDefault("Low Bar", new int(1));
	defenseChooser->AddObject("Moat", new int(2));
	defenseChooser->AddObject("Ramparts", new int(3));
	defenseChooser->AddObject("Rough Terrain", new int(4));
	defenseChooser->AddObject("Rock Wall", new int(5));
	SmartDashboard::PutData("Auton Defense",defenseChooser);
}

double OI::ReturnAutonAngle()
{

	double angle;
	switch(*(int *)positionChooser->GetSelected()){
		case 1:
			angle = Preferences::GetInstance()->GetDouble("Auton Turn Angle LowBar", -45);
			break;
		case 2:
			angle = Preferences::GetInstance()->GetDouble("Auton Turn Angle Position2",-28);
			break;
		case 3:
			angle = Preferences::GetInstance()->GetDouble("Auton Turn Angle Position3",-15);
			break;
		case 4:
			angle = Preferences::GetInstance()->GetDouble("Auton Turn Angle Position4",0);
			break;
		case 5:
			angle = Preferences::GetInstance()->GetDouble("Auton Turn Angle Position5",15);
			break;
	}
	return angle;
}

double OI::ReturnAutonDistance()
{
	double dist;
	switch(*(int *)defenseChooser->GetSelected()){
		case 1:
			dist = Preferences::GetInstance()->GetDouble("Low Bar Drive Distance", 140);
			break;
		case 2:
			dist = Preferences::GetInstance()->GetDouble("Moat Drive Distance", 150);
			break;
		case 3:
			dist = Preferences::GetInstance()->GetDouble("Ramparts Drive Distance", 140);
			break;
		case 4:
			dist = Preferences::GetInstance()->GetDouble("Rough Terrain Drive Distance", 140);
			break;
		case 5:
			dist = Preferences::GetInstance()->GetDouble("Rock Wall Drive Distance", 140);
			break;
	}
	//if(*(int *)positionChooser->GetSelected() == 2 || *(int *)positionChooser->GetSelected() == 5) dist += 49;
	return dist;
}

double OI::ReturnAutonDistHorizontal()
{
	switch(*(int *)positionChooser->GetSelected()){
		case 2:
			return Preferences::GetInstance()->GetDouble("Stop2Ball Position 2",218);
		case 3:
			return Preferences::GetInstance()->GetDouble("Stop2Ball Position 3",112);
		case 4:
			return Preferences::GetInstance()->GetDouble("Stop2Ball Position 4",160);
		case 5:
			return Preferences::GetInstance()->GetDouble("Stop2Ball Position 5",70);
		default:
			return 0;
	}
}

double OI::ReturnAutonTime()
{
	switch(*(int *)defenseChooser->GetSelected()){
		case 1:
			return Preferences::GetInstance()->GetDouble("TimeAuton LowBar",5);
		case 2:
			return Preferences::GetInstance()->GetDouble("TimeAuton Moat",5);
		case 3:
			return Preferences::GetInstance()->GetDouble("TimeAuton Ramparts",5);
		case 4:
			return Preferences::GetInstance()->GetDouble("TimeAuton Rough Terrain",4);
		case 5:
			return Preferences::GetInstance()->GetDouble("TimeAuton Rock Wall",5);
		default:
			return 5;	//Used for most drive cases
	}
}

OI* OI::GetInstance()
{
	if(!m_pInstance) m_pInstance = new OI;
	return m_pInstance;
}
