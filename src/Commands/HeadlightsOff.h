#ifndef HEADLIGHTS_OFF_H
#define HEADLIGHTS_OFF_H

#include <WPILib.h>

class HeadlightsOff: public Command
{
public:
	HeadlightsOff();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
