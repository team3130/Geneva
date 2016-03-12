#ifndef TestTurnPID_H
#define TestTurnPID_H

#include "Commands/Command.h"
#include "WPILib.h"

class TestTurnPID: public Command
{
public:
	Timer timer;
	double elapsed;
	TestTurnPID();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
