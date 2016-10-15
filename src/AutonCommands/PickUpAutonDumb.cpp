#include "PickUpAutonDumb.h"

#include "OI.h"
#include "RobotMap.h"

PickUpAutonDumb::PickUpAutonDumb()
{
	Intake_LowerIntake = new AutonControlIntakeVertical();
	Intake_ExtendIntake = new AutonControlIntakeHorizontal();
	Intake_UnExtendIntake = new AutonControlIntakeHorizontal();
	Auton_1Ball = new OneBallAutonDumb();
	Catapult_ReadyShotOne = new ReloadCatapult(BTN_PRESET_1);
	Intake_Spin = new AutonControlIntakeWheels();

	AddSequential(Catapult_ReadyShotOne, 2);
	AddParallel(Intake_LowerIntake, 1);
	AddParallel(Intake_ExtendIntake, 1);
	AddSequential(Intake_Spin, 1); //Run intake wheels for one second
	AddSequential(Intake_UnExtendIntake, .5);
	AddSequential(Auton_1Ball);
}

PickUpAutonDumb::~PickUpAutonDumb()
{
	delete Intake_LowerIntake;
	delete Intake_ExtendIntake;
	delete Intake_UnExtendIntake;
	delete Auton_1Ball;
	delete Catapult_ReadyShotOne;
	delete Intake_Spin;
}

// Called just before this Command runs the first time
void PickUpAutonDumb::Initialize()
{

	Intake_LowerIntake->SetParam(true
	);

	Intake_ExtendIntake->setParam(
			true
	);

	Intake_UnExtendIntake->setParam(
			false
	);

	Intake_Spin->SetParam(1);
}

// Called repeatedly when this Command is scheduled to run
void PickUpAutonDumb::Execute()
{
}


// Called once after isFinished returns true
void PickUpAutonDumb::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PickUpAutonDumb::Interrupted()
{
	End();
}
