#ifndef NO_AUTON_H
#define NO_AUTON_H

#include <WPILib.h>

#include "Commands/ReloadCatapult.h"

class NoAuton: public CommandGroup
{
private:
	ReloadCatapult* Catapult_ReadyShotOne;

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
