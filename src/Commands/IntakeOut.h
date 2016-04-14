#ifndef INTAKE_OUT_H
#define INTAKE_OUT_H

#include <WPILib.h>

class IntakeOut: public Command
{
public:
	IntakeOut();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
