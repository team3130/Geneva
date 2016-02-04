#ifndef CONTROL_INTAKE_VERTICAL_H
#define CONTROL_INTAKE_VERTICAL_H

#include <WPILib.h>
#include "Misc/ToggleClass.h"

class ControlIntakeVertical: public Command
{
private:
	Toggle<bool>* IntakeArmPositionUp;
public:
	ControlIntakeVertical();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
