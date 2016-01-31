#include "RobotSensors.h"
#include "Subsystems/Catapult.h"

RobotSensors::RobotSensors()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void RobotSensors::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void RobotSensors::Execute()
{
	SmartDashboard::PutBoolean("Shooter Lower Limit",Catapult::GetInstance()->isBottomHit());
	SmartDashboard::PutNumber("Shooter Position",Catapult::GetInstance()->GetPosition());
}

// Make this return true when this Command no longer needs to run execute()
bool RobotSensors::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RobotSensors::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RobotSensors::Interrupted()
{

}
