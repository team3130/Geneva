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
	Drive_ShiftDown = new DriveShiftDown();
	Drive_TurnToDefense = new AutonTurn();
	Drive_TurnToHorizontal = new AutonTurn();
	Delay_IntakeBall = new AutonDelay();

	AddParallel(Intake_Spin, 2); //Run intake wheels for two second
	AddParallel(Intake_ExtendIntake, 1);
	AddParallel(Intake_LowerIntake, 1);
	AddSequential(Delay_IntakeBall, .5);
	AddSequential(Drive_TurnToHorizontal,1);
	AddSequential(Drive_DriveToDefense,3);
	AddParallel(Intake_UnExtendIntake, .5);
	AddSequential(Drive_ShiftDown,0.5);
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
			Preferences::GetInstance()->GetDouble("Stop2Ball Angle",94),
			false
	);

	Drive_TurnToDefense->SetParam(
			-Preferences::GetInstance()->GetDouble("Stop2Ball Angle",94),
			false
	);

	Drive_DriveToDefense->SetParam(
			OI::GetInstance()->ReturnAutonDistHorizontal(),
			0,		//Don't Turn
			Preferences::GetInstance()->GetDouble("Stop2Ball Speed",1),
			Preferences::GetInstance()->GetDouble("Stop2Ball Tolerance",1),
			false
	);

	Delay_IntakeBall->setParam(0.5);
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
