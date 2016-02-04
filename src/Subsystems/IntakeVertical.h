#ifndef INTAKE_VERTICAL_H
#define INTAKE_VERTICAL_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"

class IntakeVertical: public Subsystem
{
private:
	static IntakeVertical* m_pInstance;
	Solenoid* m_intakeActuater;
	IntakeVertical();

public:
	static IntakeVertical* GetInstance();
	void InitDefaultCommand();
	void Actuate(bool extended);
};

#endif
