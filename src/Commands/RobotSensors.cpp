#include "RobotSensors.h"
#include "Subsystems/Catapult.h"
#include "Subsystems/Chassis.h"
#include "Misc/Video.h"
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
	float turn = 0;
	float dist = 0;
	size_t nTurns = 0;

	RobotVideo::GetInstance()->mutex_lock();
	nTurns = RobotVideo::GetInstance()->HaveHeading();
	if(nTurns > 0) {
		turn = RobotVideo::GetInstance()->GetTurn(0);
		dist = RobotVideo::GetInstance()->GetDistance(0);
	}
	if(fabs(turn) > 3.0 and nTurns > 1) {
		turn = RobotVideo::GetInstance()->GetTurn(1);
		dist = RobotVideo::GetInstance()->GetDistance(1);
	}
	RobotVideo::GetInstance()->mutex_unlock();

	if (nTurns > 0) {
		if (dist > 0) {
			turn += atan2f(Preferences::GetInstance()->GetFloat("CameraOffset",RobotVideo::CAMERA_OFFSET), dist);
		}
		if (fabs(turn) < 0.4) SmartDashboard::PutBoolean("DB/LED 0", true);
		else SmartDashboard::PutBoolean("DB/LED 0", false);
	}
	else SmartDashboard::PutBoolean("DB/LED 0", false);

	SmartDashboard::PutBoolean("DB/LED 2", Catapult::GetInstance()->isBottomHit());
	SmartDashboard::PutBoolean("DB/LED 3", Chassis::GetInstance()->GetDistanceL()==0 or Chassis::GetInstance()->GetDistanceR()==0);

	std::ostringstream oss0; // Replace this one with something more important
	oss0 << "Dist:" << Chassis::GetInstance()->GetDistance();
	oss0 << " Ang:" << Chassis::GetInstance()->GetAngle();
	SmartDashboard::PutString("DB/String 0", oss0.str());

	std::ostringstream oss1;
	oss1 << "L:" << ((int)(10*Chassis::GetInstance()->GetDistanceL())) / 10;
	oss1 << ", R:" << ((int)(10*Chassis::GetInstance()->GetDistanceR())) / 10;
	SmartDashboard::PutString("DB/String 1", oss1.str());

	std::ostringstream oss2;
	oss2 << "Cat: " << Catapult::GetInstance()->GetPosition();
	SmartDashboard::PutString("DB/String 2", oss2.str());

	SmartDashboard::PutNumber("Accelerometor X", accelerometer->GetX());
	SmartDashboard::PutNumber("Accelerometor Y", accelerometer->GetY());
	SmartDashboard::PutNumber("Accelerometor Z", accelerometer->GetZ());
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
