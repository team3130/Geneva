#ifndef INTAKE_HORIZONTAL_H
#define INTAKE_HORIZONTAL_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"
#include "Misc/ToggleClass.h"

class IntakeHorizontal: public Subsystem
{
private:
	static IntakeHorizontal* m_pInstance;
	Solenoid* m_intakeActuater;
	Toggle<bool>* IntakeArmPositionOut;
	IntakeHorizontal();

public:
	static IntakeHorizontal* GetInstance();
	void InitDefaultCommand();
	void Actuate(bool extended);
	bool IsExtended() {return m_intakeActuater->Get();}
	void FlipOnChange(bool input);
	bool GetState() {return IntakeArmPositionOut->getStatus();}
};

#endif
