#include "AutonCommands/1BallReturn.h"

#include "OI.h"

OneBallReturn::OneBallReturn()
{
	Auton_1Ball = new OneBallAuton();
	Catapult_DriveCatDown = new AutonCatapult();
	Intake_IntakeDown = new AutonControlIntakeVertical();
	Intake_IntakeOut = new AutonControlIntakeHorizontal();
	Intake_PinsRelease = new AutonPintake();
	Drive_BackAcrossDefense = new AutonDriveToPoint();
	Drive_TurnBackToDefense = new AutonTurn();

	AddSequential(Auton_1Ball);
	AddParallel(Catapult_DriveCatDown, 2);
	AddParallel(Intake_IntakeDown, 1);
	AddParallel(Intake_IntakeOut, 1);
	AddParallel(Intake_PinsRelease, 1);
	AddSequential(Drive_TurnBackToDefense);
	AddSequential(Drive_BackAcrossDefense);
}

OneBallReturn::~OneBallReturn()
{
	delete Auton_1Ball;
	delete Catapult_DriveCatDown;
	delete Intake_IntakeDown;
	delete Intake_IntakeOut;
	delete Intake_PinsRelease;
	delete Drive_BackAcrossDefense;
	delete Drive_TurnBackToDefense;
}

// Called just before this Command runs the first time
void OneBallReturn::Initialize()
{
	Catapult_DriveCatDown->SetParam(5,0.2);		//Doesn't Need preferences, just resets catapult.

	Intake_IntakeDown->SetParam(true);			//Won't require Tuning
	Intake_IntakeOut->setParam(true);			//Won't require Tuning
	Intake_PinsRelease->SetParam(true);			//Won't require Tuning

	Drive_TurnBackToDefense->SetParam(
			-OI::GetInstance()->ReturnAutonAngle()
	);
	Drive_BackAcrossDefense->SetParam(
			Preferences::GetInstance()->GetDouble("1BallReturn DriveBack Distance" -105),
			Preferences::GetInstance()->GetDouble("1BallReturn DriveBack Angle", 0),
			Preferences::GetInstance()->GetDouble("1BallReturn DriveBack Speed", -1),
			Preferences::GetInstance()->GetDouble("1BallReturn DriveBack Tolerance", 0.5)
	);
}

// Called repeatedly when this Command is scheduled to run
void OneBallReturn::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool OneBallReturn::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void OneBallReturn::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OneBallReturn::Interrupted()
{
	End();
}
