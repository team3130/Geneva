#include "HandleStopPoints.h"
#include "Subsystems/CatStopCalculations.h"
#include "Subsystems/Catapult.h"
#include "Misc/Video.h"

HandleStopPoints::HandleStopPoints()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void HandleStopPoints::Initialize()
{
	double dist = RobotVideo::GetInstance()->GetDistance(0);
	double stop = Catapult::GetInstance()->GetPosition();
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
