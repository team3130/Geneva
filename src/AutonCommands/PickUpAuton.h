#ifndef PICK_UP_AUTON_H
#define PICK_UP_AUTON_H

#include <WPILib.h>

#include "AutonControlIntakeVertical.h"
#include "AutonControlIntakeHorizontal.h"
#include "AutonControlIntakeWheels.h"
#include "1BallAuton.h"
#include "Commands/ReloadCatapult.h"

class PickUpAuton: public CommandGroup
{
private:
	ReloadCatapult* Catapult_ReadyShotOne;
	AutonControlIntakeVertical* Intake_LowerIntake;

	AutonControlIntakeHorizontal* Intake_ExtendIntake;
	AutonControlIntakeHorizontal* Intake_UnExtendIntake;
	AutonControlIntakeWheels* Intake_Spin;

	OneBallAuton* Auton_1Ball;


public:
	PickUpAuton();
	~PickUpAuton();
	void Initialize();
	void Execute();
	void End();
	void Interrupted();
};

#endif
