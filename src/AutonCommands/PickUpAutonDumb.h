#ifndef PICK_UP_AUTON_DUMB_H
#define PICK_UP_AUTON_DUMB_H

#include <WPILib.h>

#include "AutonControlIntakeVertical.h"
#include "AutonControlIntakeHorizontal.h"
#include "AutonControlIntakeWheels.h"
#include "1BallAutonDumb.h"
#include "Commands/ReloadCatapult.h"

class PickUpAutonDumb: public CommandGroup
{
private:
	ReloadCatapult* Catapult_ReadyShotOne;
	AutonControlIntakeVertical* Intake_LowerIntake;

	AutonControlIntakeHorizontal* Intake_ExtendIntake;
	AutonControlIntakeHorizontal* Intake_UnExtendIntake;
	AutonControlIntakeWheels* Intake_Spin;

	OneBallAutonDumb* Auton_1Ball;


public:
	PickUpAutonDumb();
	~PickUpAutonDumb();
	void Initialize();
	void Execute();
	void End();
	void Interrupted();
};

#endif
