#ifndef PinchBall_H
#define PinchBall_H

#include "WPILib.h"

class PinchBall: public Command
{
public:
	PinchBall();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
