#ifndef SAVE_STOP_POINTS_H
#define SAVE_STOP_POINTS_H

#include <WPILib.h>

class SaveStopPoints: public Command
{
public:
	SaveStopPoints();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
