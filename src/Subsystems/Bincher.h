#ifndef Bincher_H
#define Bincher_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Bincher: public Subsystem
{
private:
	static Bincher* m_pInstance;
	Solenoid* m_actuator;
	Bincher();
public:
	void InitDefaultCommand();
	static Bincher* GetInstance();
	void Actuate(bool extended);
};

#endif
