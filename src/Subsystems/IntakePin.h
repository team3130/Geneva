#ifndef INTAKE_PIN_H
#define INTAKE_PIN_H

#include "Commands/Subsystem.h"
#include "Misc/ToggleClass.h"
#include "WPILib.h"

class IntakePin: public Subsystem
{
private:
	static IntakePin* m_pInstance;
	Solenoid* m_actuator;
	Toggle<bool>* m_pinState;
	IntakePin();
public:
	void InitDefaultCommand();
	static IntakePin* GetInstance();
	void Actuate(bool extended);
	void ActuateToggle(bool toggle);
	bool IsActive() {return m_actuator->Get();};
};

#endif
