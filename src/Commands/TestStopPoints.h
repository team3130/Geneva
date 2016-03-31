#ifndef TestStopPoints_H
#define TestStopPoints_H

#include "WPILib.h"

class TestStopPoints: public Command
{
	Timer m_timer;
public:
	TestStopPoints();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
