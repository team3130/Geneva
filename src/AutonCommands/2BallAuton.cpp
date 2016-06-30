#include "AutonCommands/2BallAuton.h"

#include "Subsystems/Chassis.h"
#include "OI.h"

TwoBallAuton::TwoBallAuton()
{
	Auton_Ball1 = new OneBallAuton();
	Auton_Ball2 = new OneBallAuton();

	Intake_IntakeDown = new AutonControlIntakeVertical();
	Intake_IntakeOut = new AutonControlIntakeHorizontal();
	Intake_PinsRelease = new AutonPintake();

	Intake_BallPickupPositionHorizontal = new AutonControlIntakeHorizontal();
	Intake_BallPickupPositionVertical = new AutonControlIntakeVertical();
	Intake_BallPickupPositionPins = new AutonPintake();
	Intake_PickupBall = new AutonControlIntakeWheels();

	Drive_BackAcrossDefense = new AutonDriveToPoint();
	Drive_ToBall = new AutonDriveToPoint();
	Drive_TurnBackToDefense = new AutonTurn();

	AddSequential(Auton_Ball1);
	AddParallel(Intake_IntakeDown, 1);
	AddParallel(Intake_PinsRelease, 1);
	AddParallel(Intake_IntakeOut, 1);
	AddSequential(Drive_TurnBackToDefense, 1);
	AddSequential(Drive_BackAcrossDefense, 5);
	AddParallel(Intake_BallPickupPositionHorizontal, 1);
	AddParallel(Intake_BallPickupPositionPins, 1);
	AddParallel(Intake_BallPickupPositionVertical, 1);
	AddParallel(Intake_PickupBall, 3);
	AddSequential(Drive_ToBall, 2);
	AddSequential(Auton_Ball2);
}

TwoBallAuton::~TwoBallAuton()
{
	delete Auton_Ball1;
	delete Auton_Ball2;
	delete Intake_IntakeDown;
	delete Intake_IntakeOut;
	delete Intake_PinsRelease;
	delete Intake_BallPickupPositionHorizontal;
	delete Intake_BallPickupPositionVertical;
	delete Intake_BallPickupPositionPins;
	delete Drive_BackAcrossDefense;
	delete Drive_ToBall;
	delete Drive_TurnBackToDefense;
}

// Called just before this Command runs the first time
void TwoBallAuton::Initialize()
{
	bool intakePosition = false;
	if (*(int *)OI::GetInstance()->positionChooser->GetSelected() == 1) intakePosition = true;
	Intake_IntakeDown->SetParam(intakePosition);			//Won't require Tuning
	Intake_IntakeOut->setParam(intakePosition);				//Won't require Tuning
	Intake_PinsRelease->SetParam(intakePosition);			//Won't require Tuning

	Intake_BallPickupPositionHorizontal->setParam(true);	//Won't require Tuning
	Intake_BallPickupPositionVertical->SetParam(true);		//Won't require Tuning
	Intake_BallPickupPositionPins->SetParam(false);			//Won't require Tuning
	Intake_PickupBall->SetParam(1);

	Drive_TurnBackToDefense->SetParam(
			Chassis::GetInstance()->GetAngle(),
			true
	);

	Drive_BackAcrossDefense->SetParam(
			-OI::GetInstance()->ReturnAutonDistance() + Preferences::GetInstance()->GetDouble("2Ball DriveBack DistMod", 20),
			0,		//Don't turn
			Preferences::GetInstance()->GetDouble("2Ball DriveBack Speed", 1),
			Preferences::GetInstance()->GetDouble("2Ball DriveBack Tolerance", 0.5),
			true
	);

	Drive_ToBall->SetParam(
			-Preferences::GetInstance()->GetDouble("2Ball DriveBack DistMod", 20)
				-Preferences::GetInstance()->GetDouble("2Ball Pickup OverShoot", 10),
			0,		//Don't turn
			Preferences::GetInstance()->GetDouble("2Ball Pickup Speed", 1),
			Preferences::GetInstance()->GetDouble("2Ball Pickup Tolerance", 0.5),
			true
	);

}

// Called repeatedly when this Command is scheduled to run
void TwoBallAuton::Execute()
{
}

// Called once after isFinished returns true
void TwoBallAuton::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TwoBallAuton::Interrupted()
{
	End();
}
