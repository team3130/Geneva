#ifndef ONE_BALL_RETURN_H
#define ONE_BALL_RETURN_H

#include <WPILib.h>
#include "1BallAuton.h"
#include "AutonTurn.h"
#include "AutonDriveToPoint.h"
#include "AutonControlIntakeVertical.h"
#include "AutonControlIntakeHorizontal.h"
#include "AutonPintake.h"
#include "AutonCatapult.h"

class OneBallReturn: public CommandGroup
{
private:
	OneBallAuton* Auton_1Ball;

	AutonCatapult* Catapult_DriveCatDown;

	AutonControlIntakeVertical* Intake_IntakeDown;
	AutonControlIntakeHorizontal* Intake_IntakeOut;
	AutonPintake* Intake_PinsRelease;

	AutonTurn* Drive_TurnBackToDefense;
	AutonDriveToPoint* Drive_BackAcrossDefense;

public:
	OneBallReturn();
	~OneBallReturn();
	void Initialize();
	void Execute();
	void End();
	void Interrupted();
};

#endif
