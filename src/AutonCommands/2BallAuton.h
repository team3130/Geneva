#ifndef TWO_BALL_AUTON_H
#define TWO_BALL_AUTON_H

#include <WPILib.h>
#include "1BallAuton.h"
#include "AutonTurn.h"
#include "AutonDriveToPoint.h"
#include "AutonControlIntakeVertical.h"
#include "AutonControlIntakeHorizontal.h"
#include "AutonPintake.h"
#include "AutonControlIntakeWheels.h"

class TwoBallAuton: public CommandGroup
{
private:
	OneBallAuton* Auton_Ball1;
	OneBallAuton* Auton_Ball2;

	AutonControlIntakeVertical* Intake_IntakeDown;
	AutonControlIntakeHorizontal* Intake_IntakeOut;
	AutonPintake* Intake_PinsRelease;

	AutonPintake* Intake_BallPickupPositionPins;
	AutonControlIntakeHorizontal* Intake_BallPickupPositionHorizontal;
	AutonControlIntakeVertical* Intake_BallPickupPositionVertical;
	AutonControlIntakeWheels* Intake_PickupBall;

	AutonTurn* Drive_TurnBackToDefense;
	AutonDriveToPoint* Drive_BackAcrossDefense;
	AutonDriveToPoint* Drive_ToBall;

public:
	TwoBallAuton();
	~TwoBallAuton();
	void Initialize();
	void Execute();
	void End();
	void Interrupted();
};

#endif
