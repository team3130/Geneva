#ifndef HANDLE_STOP_POINTS_H
#define HANDLE_STOP_POINTS_H

#include <WPILib.h>

class HandleStopPoints: public Command
{
public:
	HandleStopPoints();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
