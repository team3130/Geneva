#include "1BallAuton.h"

#include "AutonCatapult.h"
#include "AutonControlIntakeVertical.h"
#include "AutonDriveToPoint.h"
#include "Commands/ControlCatapultFire.h"
#include "AutonTurn.h"
#include "Commands/CameraAim.h"

OneBallAuton::OneBallAuton()
{
	Catapult_ReadyShotOne = new AutonCatapult();
	Catapult_ShootOne = new ControlCatapultFire(true);
	Intake_LowerIntake = new AutonControlIntakeVertical();
	Intake_RaiseIntake = new AutonControlIntakeVertical();
	Intake_ExtendIntake = new AutonControlIntakeHorizontal();
	Drive_DriveToDefense = new AutonDriveToPoint();
	Turn_TurnToSeeTarget = new AutonTurn();
	Vision_AimAtTarget = new CameraAim();

	AddParallel(Intake_LowerIntake, 1);
	AddParallel(Catapult_ReadyShotOne, 2);
	AddSequential(Drive_DriveToDefense, 5);
	AddParallel(Intake_RaiseIntake, 1);
	AddParallel(Intake_ExtendIntake, 1);
	AddSequential(Turn_TurnToSeeTarget, 2);
	AddSequential(Vision_AimAtTarget, 5);
	AddSequential(Catapult_ShootOne, 2);
}

OneBallAuton::~OneBallAuton()
{
	delete Catapult_ReadyShotOne;
	delete Catapult_ShootOne;
	delete Intake_LowerIntake;
	delete Intake_RaiseIntake;
	delete Intake_ExtendIntake;
	delete Drive_DriveToDefense;
	delete Turn_TurnToSeeTarget;
	delete Vision_AimAtTarget;
}

// Called just before this Command runs the first time
void OneBallAuton::Initialize()
{
	Catapult_ReadyShotOne->SetParam(
			Preferences::GetInstance()->GetDouble("1BallAuton StopAngle",3),
			Preferences::GetInstance()->GetDouble("1BallAuton Catapult Threshold",0.5)
	);

	Intake_LowerIntake->SetParam(true
	);

	Intake_RaiseIntake->SetParam(false
	);

	Intake_ExtendIntake->setParam(
			true
	);

	Drive_DriveToDefense->SetParam(
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Distance",60),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Angle",0),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Speed",-1),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Tolerence",0.5),
			true
	);

	Turn_TurnToSeeTarget->SetParam(
			double(OI::GetInstance()->positionChooser->GetSelected())
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
