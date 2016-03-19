#include "1BallAuton.h"

#include "AutonCatapult.h"
#include "AutonControlIntakeVertical.h"
#include "AutonDriveToPoint.h"
#include "Commands/ControlCatapultFire.h"
#include "AutonTurn.h"
#include "Commands/CameraAim.h"
#include "OI.h"

OneBallAuton::OneBallAuton()
{
	if(*(int *)OI::GetInstance()->positionChooser->GetSelected() == 1 || *(int *)OI::GetInstance()->positionChooser->GetSelected() == 2) Target_TargetAim = CameraAim::kLeft;
	else Target_TargetAim = CameraAim::kRight;

	Catapult_ReadyShotOne = new AutonCatapult();
	Catapult_ShootOne = new ControlCatapultFire(true);
	Intake_AdjustForDefense = new AutonControlIntakeVertical();
	Intake_RaiseIntake = new AutonControlIntakeVertical();
	Intake_ExtendIntake = new AutonControlIntakeHorizontal();
	Drive_ShiftDown = new AutonDriveToPoint();
	Drive_DriveToDefense = new AutonDriveToPoint();
	Turn_TurnToSeeTarget = new AutonTurn();
	Vision_AimAtTarget = new CameraAim(Target_TargetAim, true);

	AddParallel(Drive_ShiftDown, 1);
	AddParallel(Intake_AdjustForDefense, 1);
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
	delete Intake_AdjustForDefense;
	delete Intake_RaiseIntake;
	delete Intake_ExtendIntake;
	delete Drive_ShiftDown;
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

	bool intakePosition;
	if(*(int *)OI::GetInstance()->positionChooser->GetSelected() == 1)intakePosition = true;
	else intakePosition = false;
	Intake_AdjustForDefense->SetParam(
			intakePosition
	);

	Intake_RaiseIntake->SetParam(false
	);

	Intake_ExtendIntake->setParam(
			true
	);

	Drive_ShiftDown->SetParam(50,0,0,0.5,true);				//Shift Down but don't move forward.

	Drive_DriveToDefense->SetParam(
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Distance",105),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Angle",0),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Speed",-1),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Tolerence",0.5),
			true
	);

	Turn_TurnToSeeTarget->SetParam(
			OI::GetInstance()->ReturnAutonAngle()
	);
}

// Called repeatedly when this Command is scheduled to run
void OneBallAuton::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool OneBallAuton::IsFinished()
{
	return Catapult_ShootOne->IsFinished();
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
