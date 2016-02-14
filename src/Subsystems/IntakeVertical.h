#ifndef INTAKE_VERTICAL_H
#define INTAKE_VERTICAL_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"
#include "Misc/ToggleClass.h"

class IntakeVertical: public Subsystem
{
private:
	static IntakeVertical* m_pInstance;
	Solenoid* m_intakeActuater;
	Toggle<bool>* m_intakeToggle;
	IntakeVertical();

public:
	static IntakeVertical* GetInstance();
	void InitDefaultCommand();
	void Actuate(bool extended);
	void ActuateToggle(bool toggle);
	bool GetToggleState() {return m_intakeToggle->getStatus();};
};

#endif
