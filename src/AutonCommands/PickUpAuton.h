#ifndef PICK_UP_AUTON_H
#define PICK_UP_AUTON_H

#include <WPILib.h>

#include "AutonControlIntakeVertical.h"
#include "AutonControlIntakeHorizontal.h"
#include "AutonControlIntakeWheels.h"
#include "1BallAuton.h"
#include "AutonCatapult.h"

class PickUpAuton: public CommandGroup
{
private:
	AutonCatapult* Catapult_ReadyShotOne;
	AutonControlIntakeVertical* Intake_LowerIntake;
	AutonControlIntakeVertical* Intake_RaiseIntake;

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
