#include "Commands/DriveShiftUp.h"
#include "Subsystems/Chassis.h"

DriveShiftUp::DriveShiftUp()
{

}

// Called just before this Command runs the first time
void DriveShiftUp::Initialize()
{
	Chassis::GetInstance()->Shift(false);
}

// Called repeatedly when this Command is scheduled to run
void DriveShiftUp::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool DriveShiftUp::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DriveShiftUp::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveShiftUp::Interrupted()
{
	End();
}
