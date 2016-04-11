#ifndef INTAKE_IN_H
#define INTAKE_IN_H

#include <WPILib.h>

class IntakeIn: public Command
{
public:
	IntakeIn();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
