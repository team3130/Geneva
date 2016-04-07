#ifndef WIPE_STOP_POINTS_H
#define WIPE_STOP_POINTS_H

#include <WPILib.h>

class WipeStopPoints: public Command
{
public:
	WipeStopPoints();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
