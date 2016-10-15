#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "AutonCommands/AutonDriveToPoint.h"

class POVTrigger: public Trigger
{
private:
	int m_dir;
	Joystick* m_stick;
public:
	POVTrigger(Joystick* stick, int dir)
	:m_dir(dir)
	,m_stick(stick)
	{}

	~POVTrigger(){delete m_stick;}

	virtual bool Get(){return m_stick->GetPOV() == m_dir;}
};

class OI
{
private:
	OI();
	OI(OI const&);
	OI& operator=(OI const&);
	static OI* m_pInstance;

	AutonDriveToPoint* driveDistTest;
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
	JoystickButton* toPoint;
	JoystickButton* headlight;
	POVTrigger*		portcullisIntake;
	POVTrigger* 	CDFIntake;
	POVTrigger*		inIntake;
	POVTrigger*		intakeOut;

	Command* addPoint;
	Command* wipePoints;
	Command* testPoints;

	SendableChooser* positionChooser;
	SendableChooser* defenseChooser;
	double ReturnAutonAngle();
	double ReturnAutonDistance();
	double ReturnAutonDistHorizontal();		//For Stop2BallAuton
	double ReturnAutonTime();				//For 1BallAutonDumb
};
#endif
