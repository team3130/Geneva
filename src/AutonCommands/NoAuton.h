#ifndef NO_AUTON_H
#define NO_AUTON_H

#include <WPILib.h>

#include "AutonCatapult.h"

class NoAuton: public CommandGroup
{
private:
	AutonCatapult* Catapult_ReadyShotOne;

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
