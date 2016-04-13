#ifndef ONE_BALL_AUTON_H
#define ONE_BALL_AUTON_H

#include <WPILib.h>

#include "Commands/ReloadCatapult.h"
#include "AutonControlIntakeVertical.h"
#include "AutonControlIntakeHorizontal.h"
#include "AutonDriveToPoint.h"
#include "Commands/ControlCatapultFire.h"
#include "AutonTurn.h"
#include "Commands/CameraAim.h"
#include "AutonDelay.h"

class OneBallAuton: public CommandGroup
{
private:
	ReloadCatapult* Catapult_ReadyShotOne;
	ReloadCatapult* Catapult_ResetCat;

	ControlCatapultFire* Catapult_ShootOne;

	AutonControlIntakeVertical* Intake_AdjustForDefense;
	AutonControlIntakeVertical* Intake_RaiseIntake;

	AutonControlIntakeHorizontal* Intake_ExtendIntake;

	AutonDriveToPoint* Drive_DriveToDefense;
	AutonTurn* Turn_TurnToSeeTarget;

	CameraAim* Vision_AimAtTarget;

	AutonDelay* Delay_FinishAuton;

public:
	OneBallAuton();
	~OneBallAuton();
	void Initialize();
	void Execute();
	void End();
	void Interrupted();
};

#endif
