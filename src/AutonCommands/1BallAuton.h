#ifndef ONE_BALL_AUTON_H
#define ONE_BALL_AUTON_H

#include <WPILib.h>

class OneBallAuton: public CommandGroup
{
private:

public:
	OneBallAuton();
	~OneBallAuton();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
