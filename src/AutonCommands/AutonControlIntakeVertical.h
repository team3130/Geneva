#ifndef AUTON_CONTROL_INTAKE_VERTICAL_H
#define AUTON_CONTROL_INTAKE_VERTICAL_H

#include <WPILib.h>

class AutonControlIntakeVertical: public Command
{
private:
bool m_bExtend;

public:
	AutonControlIntakeVertical();
	~AutonControlIntakeVertical();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetParam(bool extend){ m_bExtend = extend;}

};

#endif
