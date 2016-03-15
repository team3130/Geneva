#ifndef AUTON_CONTROL_INTAKE_VERTICAL_H
#define AUTON_CONTROL_INTAKE_VERTICAL_H

#include <WPILib.h>

class AutonControlIntakeVertical: public Command
{
private:
Timer* timer;
bool m_bExtend;
float m_TimeOut;

public:
	AutonControlIntakeVertical();
	~AutonControlIntakeVertical();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetParam(bool extend, float timeout){ m_bExtend = extend, m_TimeOut = timeout;}

};

#endif
