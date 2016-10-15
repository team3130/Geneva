#ifndef ONE_BALL_AUTON_DUMB_H
#define ONE_BALL_AUTON_DUMB_H

#include <WPILib.h>

#include "Commands/ReloadCatapult.h"
#include "AutonControlIntakeVertical.h"
#include "AutonControlIntakeHorizontal.h"
#include "AutonDumbDrive.h"
#include "Commands/ControlCatapultFire.h"
#include "AutonTurn.h"
#include "Commands/CameraAim.h"
#include "AutonDelay.h"

class OneBallAutonDumb: public CommandGroup
{
private:
	ReloadCatapult* Catapult_ReadyShotOne;
	ReloadCatapult* Catapult_ResetCat;

	ControlCatapultFire* Catapult_ShootOne;

	AutonControlIntakeVertical* Intake_AdjustForDefense;
	AutonControlIntakeVertical* Intake_RaiseIntake;

	AutonControlIntakeHorizontal* Intake_ExtendIntake;

	AutonDumbDrive* Drive_DriveToDefense;
	AutonTurn* Turn_TurnToSeeTarget;

	CameraAim* Vision_AimAtTarget;

	AutonDelay* Delay_FinishAuton;

public:
	OneBallAutonDumb();
	~OneBallAutonDumb();
	void Initialize();
	void Execute();
	void End();
	void Interrupted();
};

#endif
