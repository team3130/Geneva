#include "DriveShift.h"
#include "Subsystems/Chassis.h"

DriveShift::DriveShift()
{

}

// Called just before this Command runs the first time
void DriveShift::Initialize()
{
	Chassis::GetInstance()->Shift(true);
}

// Called repeatedly when this Command is scheduled to run
void DriveShift::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool DriveShift::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DriveShift::End()
{
	Chassis::GetInstance()->Shift(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveShift::Interrupted()
{
	End();
}
