#include "AutonDumbDrive.h"
#include "Subsystems/Chassis.h"

AutonDumbDrive::AutonDumbDrive()
{
	m_speed = 0;
	Requires(Chassis::GetInstance());
}

// Called just before this Command runs the first time
void AutonDumbDrive::Initialize()
{
	Chassis::GetInstance()->HoldAngle(0,true);
	Chassis::GetInstance()->DriveStraight(m_speed);
}

// Called repeatedly when this Command is scheduled to run
void AutonDumbDrive::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool AutonDumbDrive::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void AutonDumbDrive::End()
{
	Chassis::GetInstance()->DriveStraight(0);
	Chassis::GetInstance()->ReleaseAngle();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonDumbDrive::Interrupted()
{
	End();
}
