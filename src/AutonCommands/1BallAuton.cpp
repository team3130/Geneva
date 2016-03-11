#include "1BallAuton.h"

#include "AutonCatapult.h"
#include "AutonControlIntakeVertical.h"
#include "AutonDriveToPoint.h"
#include "AutonFire.h"
#include "AutonTurn.h"
#include "Commands/CameraAim.h"

OneBallAuton::OneBallAuton()
{
	Catapult_ReadyShotOne = new AutonCatapult();
	Catapult_ShootOne = new AutonFire();
	Intake_LowerIntake = new AutonControlIntakeVertical();
	Drive_DriveToDefense = new AutonDriveToPoint();
	Drive_DriveToShootPosition = new AutonDriveToPoint();
	Turn_TurnToSeeTarget = new AutonTurn();
	Drive_ShiftDown = new AutonDriveToPoint();
	Vision_AimAtTarget = new CameraAim();

//	AddParallel(Bincher_HoldBall);
	AddParallel(Intake_LowerIntake);
	AddParallel(Catapult_ReadyShotOne);
//	AddSequential(Drive_ShiftDown, 0.5);
	AddSequential(Drive_DriveToDefense);
//	AddSequential(Drive_DriveToShootPosition);
	AddSequential(Turn_TurnToSeeTarget, 2);
	AddSequential(Vision_AimAtTarget, 3);
	AddSequential(Catapult_ShootOne);
}

OneBallAuton::~OneBallAuton()
{
	delete Catapult_ReadyShotOne;
	delete Catapult_ShootOne;
	delete Intake_LowerIntake;
	delete Drive_DriveToDefense;
	delete Drive_DriveToShootPosition;
	delete Turn_TurnToSeeTarget;
	delete Vision_AimAtTarget;
}

// Called just before this Command runs the first time
void OneBallAuton::Initialize()
{
	Catapult_ReadyShotOne->SetParam(
			Preferences::GetInstance()->GetDouble("1BallAuton StopAngle",3),
			Preferences::GetInstance()->GetDouble("1BallAuton Catapult Threshold",0.5),
			Preferences::GetInstance()->GetDouble("1BallAuton Catapult Timeout",5)
	);

	Catapult_ShootOne->SetParam(
			Preferences::GetInstance()->GetDouble("1BallAuton Shoot Timeout",2)
	);

	Intake_LowerIntake->SetParam(true,
			Preferences::GetInstance()->GetDouble("1BallAuton Intake Timeout",1)
	);

	Drive_ShiftDown->SetParam(
			30,				//Distance to attempt to drive
			0,				//No Angle
			0,				//Don't actually drive
			2,				//Arbitrary number significantly less than 30
			0,				//Don't timeout from command
			true			//Shift Down
	);

	Drive_DriveToDefense->SetParam(
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Distance",70),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Angle",0),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Speed",-1),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Tolerence",0.5),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Timeout", 5),
			true
	);

	Drive_DriveToShootPosition->SetParam(
			Preferences::GetInstance()->GetDouble("1BallAuton Drive2 Distance",74),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive2 Angle",0),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive2 Speed",-0.8),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive2 Tolerence",0.5),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive2 Timeout", 5),
			true
	);

	Turn_TurnToSeeTarget->SetParam(
			Preferences::GetInstance()->GetDouble("1BallAuton Turn Angle", -45)
	);
}

// Called repeatedly when this Command is scheduled to run
void OneBallAuton::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool OneBallAuton::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void OneBallAuton::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OneBallAuton::Interrupted()
{
	End();
}
