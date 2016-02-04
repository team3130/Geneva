#ifndef CONTROL_INTAKE_HORIZONTAL_H
#define CONTROL_INTAKE_HORIZONTAL_H

#include <WPILib.h>
#include "Misc/ToggleClass.h"

class ControlIntakeHorizontal: public Command
{
private:
	Toggle<bool>* IntakeArmPositionOut;
public:
	ControlIntakeHorizontal();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
