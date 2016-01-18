#ifndef NO_AUTON_H
#define NO_AUTON_H

#include "WPILib.h"

class NoAuton: public CommandGroup
{
private:

public:
	NoAuton();
	~NoAuton();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
