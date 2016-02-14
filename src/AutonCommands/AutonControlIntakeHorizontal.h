#ifndef AUTON_CONTROL_INTAKE_HORIZONTAL_H
#define AUTON_CONTROL_INTAKE_HORIZONTAL_H

#include <WPILib.h>
#include "Misc/ToggleClass.h"

class AutonControlIntakeHorizontal: public Command
{
private:

	Timer* timer;
	bool m_bExtend;
	float m_TimeOut;
public:
	AutonControlIntakeHorizontal();
	~AutonControlIntakeHorizontal();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void setParam(float timeout, bool extend){m_TimeOut = timeout, m_bExtend = extend;}
};

#endif
