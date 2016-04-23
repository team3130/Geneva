#include "Stop2BallAuton.h"

#include "OI.h"
#include "RobotMap.h"

Stop2BallAuton::Stop2BallAuton()
{
	Intake_LowerIntake = new AutonControlIntakeVertical();
	Intake_ExtendIntake = new AutonControlIntakeHorizontal();
	Intake_UnExtendIntake = new AutonControlIntakeHorizontal();
	Auton_1Ball = new OneBallAuton();
	Catapult_ReadyShotOne = new ReloadCatapult(BTN_PRESET_1);
	Intake_Spin = new AutonControlIntakeWheels();
	Drive_DriveToDefense = new AutonDriveToPoint();
	Drive_TurnToDefense = new AutonTurn();
	Drive_TurnToHorizontal = new AutonTurn();

	AddSequential(Catapult_ReadyShotOne, 2);
	AddParallel(Intake_LowerIntake, 1);
	AddParallel(Intake_ExtendIntake, 1);
	AddSequential(Intake_Spin, 1); //Run intake wheels for one second
	AddParallel(Intake_UnExtendIntake, .5);
	AddSequential(Drive_TurnToHorizontal,1);
	AddSequential(Drive_DriveToDefense,3);
	AddSequential(Drive_TurnToDefense,1);
	AddSequential(Auton_1Ball);
}

Stop2BallAuton::~Stop2BallAuton()
{
	delete Intake_LowerIntake;
	delete Intake_ExtendIntake;
	delete Intake_UnExtendIntake;
	delete Auton_1Ball;
	delete Catapult_ReadyShotOne;
	delete Intake_Spin;
	delete Drive_DriveToDefense;
	delete Drive_TurnToDefense;
	delete Drive_TurnToHorizontal;
}

// Called just before this Command runs the first time
void Stop2BallAuton::Initialize()
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

	Drive_TurnToHorizontal->SetParam(
			Preferences::GetInstance()->GetDouble("Stop2Ball Angle",-89),
			false
	);

	Drive_TurnToDefense->SetParam(
			-Preferences::GetInstance()->GetDouble("Stop2Ball Angle",-89),
			false
	);

	Drive_DriveToDefense->SetParam(
			OI::GetInstance()->ReturnAutonDistHorizontal(),
			0,		//Don't Turn
			Preferences::GetInstance()->GetDouble("Stop2Ball Speed",1),
			Preferences::GetInstance()->GetDouble("Stop2Ball Tolerance",1),
			false
	);
}

// Called repeatedly when this Command is scheduled to run
void Stop2BallAuton::Execute()
{
}


// Called once after isFinished returns true
void Stop2BallAuton::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Stop2BallAuton::Interrupted()
{
	End();
}
