#ifndef AUTON_CONTROL_INTAKE_HORIZONTAL_H
#define AUTON_CONTROL_INTAKE_HORIZONTAL_H

#include <WPILib.h>

class AutonControlIntakeHorizontal: public Command
{
private:

	bool m_bExtend;

public:
	AutonControlIntakeHorizontal();
	~AutonControlIntakeHorizontal();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void setParam(bool extend){m_bExtend = extend;}
};

#endif
