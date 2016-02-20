#include "1BallAuton.h"

#include "AutonCatapult.h"
#include "AutonControlIntakeVertical.h"
#include "AutonDriveToPoint.h"
#include "AutonFire.h"
#include "AutonPinchBall.h"
#include "AutonAim.h"

OneBallAuton::OneBallAuton()
{
	Catapult_ReadyShotOne = new AutonCatapult();
	Catapult_ShootOne = new AutonFire();
	Bincher_HoldBall = new PinchBall();
	Intake_LowerIntake = new AutonControlIntakeHorizontal();
	Drive_DriveAcrossDefense = new AutonDriveToPoint();
	Vision_AimAtTarget = new AutonAim();

	AddParallel(Bincher_HoldBall);
	AddParallel(Intake_LowerIntake);
	AddParallel(Catapult_ReadyShotOne);
	AddSequential(Drive_DriveAcrossDefense);
	AddSequential(Vision_AimAtTarget);
	AddSequential(Catapult_ShootOne);
}

OneBallAuton::~OneBallAuton()
{
	delete Catapult_ReadyShotOne;
	delete Catapult_ShootOne;
	delete Bincher_HoldBall;
	delete Intake_LowerIntake;
	delete Drive_DriveAcrossDefense;
	delete Vision_AimAtTarget;
}

// Called just before this Command runs the first time
void OneBallAuton::Initialize()
{
	Catapult_ReadyShotOne->SetParam(
			Preferences::GetInstance()->GetDouble("1BallAuton StopAngle",15),
			Preferences::GetInstance()->GetDouble("1BallAuton Catapult Threshold",0.5),
			Preferences::GetInstance()->GetDouble("1BallAuton Catapult Timeout",5)
	);

	Catapult_ShootOne->SetParam(
			Preferences::GetInstance()->GetDouble("1BallAuton Shoot Timeout",2)
	);

	Bincher_HoldBall->SetParam(true);	//Doesn't require Tuning

	Intake_LowerIntake->SetParam(true,
			Preferences::GetInstance()->GetDouble("1BallAuton Intake Timeout",1)
	);

	Drive_DriveAcrossDefense->SetParam(
			Preferences::GetInstance()->GetDouble("1BallAuton Drive Distance",100),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive Angle",0),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive Speed",-0.8),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive Tolerence",0.5),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive Timeout", 5)
	);

	Vision_AimAtTarget->SetParam(
			Preferences::GetInstance()->GetDouble("1BallAuton Aim Timeout", 4),
			Vision_AimAtTarget->kLeft	//Can't be gotten through preferences
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
