#ifndef HeadlightsOn_H
#define HeadlightsOn_H

#include "WPILib.h"

class HeadlightsOn: public Command
{
public:
	HeadlightsOn();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
