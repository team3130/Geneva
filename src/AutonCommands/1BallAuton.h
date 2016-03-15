#ifndef ONE_BALL_AUTON_H
#define ONE_BALL_AUTON_H

#include <WPILib.h>

#include "AutonCatapult.h"
#include "AutonControlIntakeVertical.h"
#include "AutonDriveToPoint.h"
#include "AutonFire.h"
#include "AutonPinchBall.h"
#include "AutonAim.h"

class OneBallAuton: public CommandGroup
{
private:
	AutonCatapult* Catapult_ReadyShotOne;

	AutonFire* Catapult_ShootOne;

	AutonPinchBall* Bincher_HoldBall;

	AutonControlIntakeVertical* Intake_LowerIntake;

	AutonDriveToPoint* Drive_DriveToDefense;
	AutonDriveToPoint* Drive_DriveToShootPosition;
	AutonDriveToPoint* Drive_TurnToSeeTarget;

	AutonAim* Vision_AimAtTarget;

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
