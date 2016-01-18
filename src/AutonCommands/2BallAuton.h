#ifndef TWO_BALL_AUTON_H
#define TWO_BALL_AUTON_H

#include "WPILib.h"

class TwoBallAuton: public CommandGroup
{
private:

public:
	TwoBallAuton();
	~TwoBallAuton();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
