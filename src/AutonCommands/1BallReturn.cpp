#include "AutonCommands/1BallReturn.h"

#include "Subsystems/Chassis.h"
#include "OI.h"

OneBallReturn::OneBallReturn()
{
	Auton_1Ball = new OneBallAuton();
	Intake_IntakeDown = new AutonControlIntakeVertical();
	Intake_IntakeOut = new AutonControlIntakeHorizontal();
	Intake_PinsRelease = new AutonPintake();
	Drive_BackAcrossDefense = new AutonDriveToPoint();
	Drive_TurnBackToDefense = new AutonTurn();

	AddSequential(Auton_1Ball);
	AddParallel(Intake_IntakeDown, 1);
	AddParallel(Intake_PinsRelease, 1);
	AddParallel(Intake_IntakeOut, 1);
	AddSequential(Drive_TurnBackToDefense, 1);
	AddSequential(Drive_BackAcrossDefense, 5);
}

OneBallReturn::~OneBallReturn()
{
	delete Auton_1Ball;
	delete Intake_IntakeDown;
	delete Intake_IntakeOut;
	delete Intake_PinsRelease;
	delete Drive_BackAcrossDefense;
	delete Drive_TurnBackToDefense;
}

// Called just before this Command runs the first time
void OneBallReturn::Initialize()
{
	bool intakePosition = false;
	if (*(int *)OI::GetInstance()->positionChooser->GetSelected() == 1) intakePosition = true;
	Intake_IntakeDown->SetParam(intakePosition);			//Won't require Tuning
	Intake_IntakeOut->setParam(intakePosition);			//Won't require Tuning
	Intake_PinsRelease->SetParam(intakePosition);			//Won't require Tuning

	Drive_TurnBackToDefense->SetParam(
			Chassis::GetInstance()->GetAngle(),
			true
	);

	Drive_BackAcrossDefense->SetParam(
			-OI::GetInstance()->ReturnAutonDistance() + 10,
			0,		//Don't turn
			Preferences::GetInstance()->GetDouble("1BallReturn DriveBack Speed", 1),
			Preferences::GetInstance()->GetDouble("1BallReturn DriveBack Tolerance", 0.5),
			true
	);
}

// Called repeatedly when this Command is scheduled to run
void OneBallReturn::Execute()
{
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
