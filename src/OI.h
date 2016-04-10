#ifndef OI_H
#define OI_H

#include "WPILib.h"

class AXSTrigger: public Trigger
{
private:
	int m_axs;
	float m_threshold;
	Joystick* m_stick;
public:
	AXSTrigger(Joystick* stick, int axs, float threshold)
	:m_axs(axs)
	,m_threshold(threshold)
	,m_stick(stick)
	{}

	~AXSTrigger(){delete m_stick;}

	virtual bool Get(){return m_stick->GetRawAxis(m_axs) > m_threshold;}
};

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
	JoystickButton* portcullis;
	AXSTrigger* 	CDFIntake;

	Command* addPoint;
	Command* wipePoints;
	Command* testPoints;

	SendableChooser* positionChooser;
	SendableChooser* defenseChooser;
	double ReturnAutonAngle();
	double ReturnAutonDistance();
};

#endif
