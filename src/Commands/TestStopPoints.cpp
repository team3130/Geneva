#include "TestStopPoints.h"
#include "Subsystems/CatStopCalculations.h"

TestStopPoints::TestStopPoints()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	this->SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void TestStopPoints::Initialize()
{
	m_timer.Reset();
	m_timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void TestStopPoints::Execute()
{
	double dist = 36.0 + 10*m_timer.Get();
	SmartDashboard::PutNumber("Test stop curve", CatStopCalculations::GetInstance()->GetStop(dist));
}

// Make this return true when this Command no longer needs to run execute()
bool TestStopPoints::IsFinished()
{
	return m_timer.Get() > 25.0;
}

// Called once after isFinished returns true
void TestStopPoints::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestStopPoints::Interrupted()
{

}
