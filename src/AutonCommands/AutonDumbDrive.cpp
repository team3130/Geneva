#include "AutonDumbDrive.h"
#include "Subsystems/Chassis.h"

AutonDumbDrive::AutonDumbDrive():
	m_speed(0),
	m_timeDrive(0),
	m_shiftLow(true)
{
	timer = new Timer();
	Requires(Chassis::GetInstance());
}

// Called just before this Command runs the first time

AutonDumbDrive::~AutonDumbDrive()
{
	delete timer;
}

void AutonDumbDrive::Initialize()
{
	timer->Start();
	Chassis::GetInstance()->Shift(m_shiftLow);
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
	return timer->Get() > m_timeDrive;
}

// Called once after isFinished returns true
void AutonDumbDrive::End()
{
	timer->Stop();
	Chassis::GetInstance()->ReleaseAngle();
	Chassis::GetInstance()->Drive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonDumbDrive::Interrupted()
{
	End();
}

void AutonDumbDrive::SetParam(float time, float speed, bool shiftLow)
{
	m_speed = speed;
	m_timeDrive = time;
	m_shiftLow = shiftLow;
}
