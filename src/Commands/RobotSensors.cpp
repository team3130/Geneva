#include "RobotSensors.h"
#include "Subsystems/Catapult.h"
#include "Subsystems/Chassis.h"
#include "OI.h"

RobotSensors::RobotSensors()
{
	this->SetRunWhenDisabled(true);
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
	std::ostringstream oss0;
	oss0 << "Dist:" << Chassis::GetInstance()->GetDistance();
	oss0 << " Ang:" << Chassis::GetInstance()->GetAngle();
	SmartDashboard::PutString("DB/String 0", oss0.str());

	SmartDashboard::PutNumber("POV Angles",OI::GetInstance()->gamepad->GetPOV());
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
