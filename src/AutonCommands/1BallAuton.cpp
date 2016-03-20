#include "1BallAuton.h"

#include "RobotMap.h"
#include "Commands/ReloadCatapult.h"
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

	Catapult_ReadyShotOne = new ReloadCatapult(BTN_PRESET_1);
	Catapult_ShootOne = new ControlCatapultFire(true);
	Intake_AdjustForDefense = new AutonControlIntakeVertical();
	Intake_RaiseIntake = new AutonControlIntakeVertical();
	Intake_ExtendIntake = new AutonControlIntakeHorizontal();
	Drive_DriveToDefense = new AutonDriveToPoint();
	Turn_TurnToSeeTarget = new AutonTurn();
	Vision_AimAtTarget = new CameraAim(Target_TargetAim, true);
	Delay_FinishAuton = new AutonDelay();

	AddParallel(Intake_AdjustForDefense, 1);
	AddParallel(Catapult_ReadyShotOne, 2);
	AddSequential(Drive_DriveToDefense, 5);
	AddParallel(Intake_RaiseIntake, 1);
	AddParallel(Intake_ExtendIntake, 1);
	AddSequential(Turn_TurnToSeeTarget, 2);
	AddSequential(Vision_AimAtTarget, 5);
	AddSequential(Catapult_ShootOne, 1);
	AddSequential(Delay_FinishAuton);
}

OneBallAuton::~OneBallAuton()
{
	delete Catapult_ReadyShotOne;
	delete Catapult_ShootOne;
	delete Intake_AdjustForDefense;
	delete Intake_RaiseIntake;
	delete Intake_ExtendIntake;
	delete Drive_DriveToDefense;
	delete Turn_TurnToSeeTarget;
	delete Vision_AimAtTarget;
	delete Delay_FinishAuton;
}

// Called just before this Command runs the first time
void OneBallAuton::Initialize()
{
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

	Drive_DriveToDefense->SetParam(
			OI::GetInstance()->ReturnAutonDistance(),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Angle",0),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Speed",1),
			Preferences::GetInstance()->GetDouble("1BallAuton Drive1 Tolerence",0.5),
			true
	);

	Turn_TurnToSeeTarget->SetParam(
			OI::GetInstance()->ReturnAutonAngle()
	);

	Delay_FinishAuton->setParam(0);
}

// Called repeatedly when this Command is scheduled to run
void OneBallAuton::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool OneBallAuton::IsFinished()
{
	return Delay_FinishAuton->IsFinished();
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
