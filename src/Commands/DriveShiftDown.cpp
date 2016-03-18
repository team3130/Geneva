#include "DriveShiftDown.h"
#include "Subsystems/Chassis.h"

DriveShiftDown::DriveShiftDown()
{

}

// Called just before this Command runs the first time
void DriveShiftDown::Initialize()
{
	Chassis::GetInstance()->Shift(true);
}

// Called repeatedly when this Command is scheduled to run
void DriveShiftDown::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool DriveShiftDown::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DriveShiftDown::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveShiftDown::Interrupted()
{
	End();
}
