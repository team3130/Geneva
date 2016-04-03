#include "HandleStopPoints.h"
#include "Subsystems/CatStopCalculations.h"
#include "Subsystems/Catapult.h"
#include "Misc/Video.h"

HandleStopPoints::HandleStopPoints()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	this->SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void HandleStopPoints::Initialize()
{
	double dist = Preferences::GetInstance()->GetDouble("CatStop Distance",0);
	double stop = Preferences::GetInstance()->GetDouble("CatStop Stop Angle", 0);
	if(dist == 0) dist = RobotVideo::GetInstance()->GetDistance(0);
	if(stop == 0) stop = Preferences::GetInstance()->GetDouble("WinchPositionE", Catapult::GetInstance()->GetPosition());
	CatStopCalculations::GetInstance()->AddPoint(dist, stop);
}

// Called repeatedly when this Command is scheduled to run
void HandleStopPoints::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool HandleStopPoints::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void HandleStopPoints::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HandleStopPoints::Interrupted()
{

}
