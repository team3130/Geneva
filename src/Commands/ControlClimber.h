#ifndef ControlClimber_H
#define ControlClimber_H


#include "WPILib.h"

class ControlClimber: public Command
{
public:
	ControlClimber();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
