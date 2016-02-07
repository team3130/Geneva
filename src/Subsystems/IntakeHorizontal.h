#ifndef INTAKE_HORIZONTAL_H
#define INTAKE_HORIZONTAL_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"

class IntakeHorizontal: public Subsystem
{
private:
	static IntakeHorizontal* m_pInstance;
	Solenoid* m_intakeActuater;
	IntakeHorizontal();

public:
	static IntakeHorizontal* GetInstance();
	void InitDefaultCommand();
	void Actuate(bool extended);
};

#endif
