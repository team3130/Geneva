#ifndef INTAKE_PIN_H
#define INTAKE_PIN_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class IntakePin: public Subsystem
{
private:
	static IntakePin* m_pInstance;
	Solenoid* m_actuator;
	IntakePin();
public:
	void InitDefaultCommand();
	static IntakePin* GetInstance();
	void Actuate(bool extended);
	bool IsActive() {return m_actuator->Get();};
};

#endif
