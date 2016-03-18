#include "PickUpAuton.h"

#include "1BallAuton.h"
#include "AutonCatapult.h"
#include "AutonControlIntakeVertical.h"
#include "AutonControlIntakeHorizontal.h"
#include "AutonControlIntakeWheels.h"
#include "OI.h"

PickUpAuton::PickUpAuton()
{
	Intake_LowerIntake = new AutonControlIntakeVertical();
	Intake_RaiseIntake = new AutonControlIntakeVertical();
	Intake_ExtendIntake = new AutonControlIntakeHorizontal();
	Intake_UnExtendIntake = new AutonControlIntakeHorizontal();
	Auton_1Ball = new OneBallAuton();
	Catapult_ReadyShotOne = new AutonCatapult();
	Intake_Spin = new AutonControlIntakeWheels();

	AddSequential(Catapult_ReadyShotOne, 2);
	AddParallel(Intake_LowerIntake, 1);
	AddParallel(Intake_ExtendIntake, 1);
	AddSequential(Intake_Spin, 2); //Run intake wheels for two seconds
	AddParallel(Intake_UnExtendIntake, 1);
	AddSequential(Auton_1Ball);
}

PickUpAuton::~PickUpAuton()
{
	delete Intake_LowerIntake;
	delete Intake_ExtendIntake;
	delete Intake_UnExtendIntake;
	delete Auton_1Ball;
	delete Catapult_ReadyShotOne;
	delete Intake_Spin;
}

// Called just before this Command runs the first time
void PickUpAuton::Initialize()
{

	Intake_LowerIntake->SetParam(true
	);

	Intake_ExtendIntake->setParam(
			true
	);

	Intake_UnExtendIntake->setParam(
			false
	);

	//Intake_Spin->setParam(); Not sure what needs to be done to get the spin for 2 seconds

	Catapult_ReadyShotOne->SetParam(
			Preferences::GetInstance()->GetDouble("1BallAuton StopAngle",3),
			Preferences::GetInstance()->GetDouble("1BallAuton Catapult Threshold",0.5)
	);







}

// Called repeatedly when this Command is scheduled to run
void PickUpAuton::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool PickUpAuton::IsFinished()
{
	return Auton_1Ball->IsFinished();
}

// Called once after isFinished returns true
void PickUpAuton::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PickUpAuton::Interrupted()
{
	End();
}
