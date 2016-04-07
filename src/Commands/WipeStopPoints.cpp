#include "WipeStopPoints.h"
#include "Subsystems/CatStopCalculations.h"

WipeStopPoints::WipeStopPoints()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void WipeStopPoints::Initialize()
{
	CatStopCalculations::GetInstance()->WipeSave();
}

// Called repeatedly when this Command is scheduled to run
void WipeStopPoints::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool WipeStopPoints::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void WipeStopPoints::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WipeStopPoints::Interrupted()
{

}
