#include "TestTurnPID.h"
#include "Subsystems/Chassis.h"
#include "OI.h"

TestTurnPID::TestTurnPID()
	: elapsed(0)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Chassis::GetInstance());
}

// Called just before this Command runs the first time
void TestTurnPID::Initialize()
{
	Chassis::GetInstance()->ResetPID();
	Chassis::GetInstance()->SetAbsoluteTolerance(0.4);
	Chassis::GetInstance()->Shift(true);
	Chassis::GetInstance()->HoldAngle(SmartDashboard::GetNumber("Test Turn Angle", -20.0));
	elapsed = 0;
	timer.Reset();
	timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void TestTurnPID::Execute()
{
	if (Chassis::GetInstance()->OnTarget()) {
		if (elapsed == 0) elapsed = timer.Get();
	}
	double moveSpeed = -OI::GetInstance()->stickL->GetY();
	moveSpeed *= fabs(moveSpeed); // Square it here so the drivers will feel like it's squared
	Chassis::GetInstance()->DriveStraight(moveSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool TestTurnPID::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void TestTurnPID::End()
{
	SmartDashboard::PutNumber("Test Turn Time", elapsed);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestTurnPID::Interrupted()
{
	End();
}
