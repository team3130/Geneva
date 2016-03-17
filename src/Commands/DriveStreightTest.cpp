#include "DriveStreightTest.h"
#include "Subsystems/Chassis.h"
#include "OI.h"

DriveStreightTest::DriveStreightTest()
{
	Requires(Chassis::GetInstance());
}

// Called just before this Command runs the first time
void DriveStreightTest::Initialize()
{
	Chassis::GetInstance()->HoldAngle(Preferences::GetInstance()->GetDouble("TestAngle",0));
}

// Called repeatedly when this Command is scheduled to run
void DriveStreightTest::Execute()
{
	Chassis::GetInstance()->DriveStraight(-OI::GetInstance()->stickL->GetY());
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStreightTest::IsFinished()
{
	return !OI::GetInstance()->streight->Get();
}

// Called once after isFinished returns true
void DriveStreightTest::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStreightTest::Interrupted()
{
	End();
}
