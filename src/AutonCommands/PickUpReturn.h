#ifndef PICK_UP_RETURN_H
#define PICK_UP_RETURN_H

#include <WPILib.h>

#include "AutonControlIntakeVertical.h"
#include "AutonControlIntakeHorizontal.h"
#include "AutonControlIntakeWheels.h"
#include "1BallReturn.h"
#include "Commands/ReloadCatapult.h"

class PickUpReturn: public CommandGroup
{
private:
	ReloadCatapult* Catapult_ReadyShotOne;
	AutonControlIntakeVertical* Intake_LowerIntake;

	AutonControlIntakeHorizontal* Intake_ExtendIntake;
	AutonControlIntakeHorizontal* Intake_UnExtendIntake;
	AutonControlIntakeWheels* Intake_Spin;

	OneBallReturn* Auton_1BallReturn;


public:
	PickUpReturn();
	~PickUpReturn();
	void Initialize();
	void Execute();
	void End();
	void Interrupted();
};

#endif
