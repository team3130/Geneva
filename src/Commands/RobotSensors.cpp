#include "RobotSensors.h"
#include "Subsystems/Catapult.h"
#include "Subsystems/Chassis.h"
#include "OI.h"

RobotSensors::RobotSensors()
{
	accelerometer = new BuiltInAccelerometer();
	this->SetRunWhenDisabled(true);
}

RobotSensors::~RobotSensors()
{
	delete accelerometer;
}

// Called just before this Command runs the first time
void RobotSensors::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void RobotSensors::Execute()
{
	SmartDashboard::PutBoolean("DB/LED 0", Catapult::GetInstance()->isBottomHit());
	SmartDashboard::PutBoolean("DB/LED 1", Chassis::GetInstance()->GetDistanceL()==0 or Chassis::GetInstance()->GetDistanceR()==0);

	std::ostringstream oss0; // Replace this one with something more important
	oss0 << "Dist:" << Chassis::GetInstance()->GetDistance();
	oss0 << " S:" << Chassis::GetInstance()->GetSpeed();
	SmartDashboard::PutString("DB/String 0", oss0.str());

	std::ostringstream oss1;
	oss1 << "L:" << ((int)(10*Chassis::GetInstance()->GetDistanceL())) / 10;
	oss1 << ", R:" << ((int)(10*Chassis::GetInstance()->GetDistanceR())) / 10;
	SmartDashboard::PutString("DB/String 1", oss1.str());

	std::ostringstream oss2;
	oss2 << "Cat: " << Catapult::GetInstance()->GetPosition();
	SmartDashboard::PutString("DB/String 2", oss2.str());

	std::ostringstream oss3; // Replace this one with something more important
	oss3 << " Angle:" << Chassis::GetInstance()->GetAngle();
	SmartDashboard::PutString("DB/String 3", oss3.str());

	SmartDashboard::PutNumber("Accelerometor X", accelerometer->GetX());
	SmartDashboard::PutNumber("Accelerometor Y", accelerometer->GetY());
	SmartDashboard::PutNumber("Accelerometor Z", accelerometer->GetZ());

	SmartDashboard::PutNumber("Line Follower Value", Catapult::GetInstance()->BallPresentValue());
	SmartDashboard::PutBoolean("Ball Present", Catapult::GetInstance()->IsBallPresent());

	// Take this measurement for tuning purposes. Remove after the tuning is done
	SmartDashboard::PutNumber("Linear Velocity", Chassis::GetInstance()->GetSpeed());

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
