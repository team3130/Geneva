#ifndef STOP_TWO_BALL_AUTON_H
#define STOP_TWO_BALL_AUTON_H

#include <WPILib.h>

#include "AutonControlIntakeVertical.h"
#include "AutonControlIntakeHorizontal.h"
#include "AutonControlIntakeWheels.h"
#include "AutonTurn.h"
#include "AutonDriveToPoint.h"
#include "1BallAuton.h"
#include "Commands/ReloadCatapult.h"

class Stop2BallAuton: public CommandGroup
{
private:
	ReloadCatapult* Catapult_ReadyShotOne;
	AutonControlIntakeVertical* Intake_LowerIntake;

	AutonControlIntakeHorizontal* Intake_ExtendIntake;
	AutonControlIntakeHorizontal* Intake_UnExtendIntake;
	AutonControlIntakeWheels* Intake_Spin;

	AutonTurn* Drive_TurnToHorizontal;
	AutonTurn* Drive_TurnToDefense;
	AutonDriveToPoint* Drive_DriveToDefense;

	OneBallAuton* Auton_1Ball;


public:
	Stop2BallAuton();
	~Stop2BallAuton();
	void Initialize();
	void Execute();
	void End();
	void Interrupted();
};

#endif
