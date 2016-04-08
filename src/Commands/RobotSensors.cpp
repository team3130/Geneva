#include "RobotSensors.h"
#include "Subsystems/Catapult.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/IntakeHorizontal.h"
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
	SmartDashboard::PutString("DB/String 9", "# Zero!! #");
	SmartDashboard::PutString("DB/String 8", "# Check Encoders #");
}

void PutBasicNumber(int line, std::string name, double value)
{
	std::ostringstream ossKey, ossVal;
	ossKey << "DB/String " << line;
	ossVal << name << ": " << value;
	SmartDashboard::PutString(ossKey.str(), ossVal.str());
}

// Called repeatedly when this Command is scheduled to run
void RobotSensors::Execute()
{
	//    Basic Dash. The main "DB/LED 0" is used for aiming and lit by CameraAim command.
	SmartDashboard::PutBoolean("DB/LED 2", Catapult::GetInstance()->isBottomHit());

	PutBasicNumber(0, "Cat", Catapult::GetInstance()->GetPosition());

	std::ostringstream oss1;
	oss1 << "L:" << ((int)(10*Chassis::GetInstance()->GetDistanceL())) / 10;
	oss1 << ", R:" << ((int)(10*Chassis::GetInstance()->GetDistanceR())) / 10;
	SmartDashboard::PutString("DB/String 1", oss1.str());

	PutBasicNumber(3, "Angle", Chassis::GetInstance()->GetAngle());
	PutBasicNumber(4, "Speed", Chassis::GetInstance()->GetSpeed());


	if (Chassis::GetInstance()->GetDistanceL()!=0 and Chassis::GetInstance()->GetDistanceR()!=0) {
		SmartDashboard::PutString("DB/String 8", "");
	}

	if (Catapult::GetInstance()->CheckZero()) {
		SmartDashboard::PutString("DB/String 9", "");
	}

	SmartDashboard::PutBoolean("Intake Position",IntakeHorizontal::GetInstance()->GetState());
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
