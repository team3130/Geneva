#ifndef CONTROL_INTAKE_HORIZONTAL_H
#define CONTROL_INTAKE_HORIZONTAL_H

#include <WPILib.h>

class ControlIntakeHorizontal: public Command
{
private:
public:
	ControlIntakeHorizontal();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
