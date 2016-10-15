#include "HeadlightsOff.h"
#include "Subsystems/Headlights.h"

HeadlightsOff::HeadlightsOff()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Headlights::GetInstance());
}

// Called just before this Command runs the first time
void HeadlightsOff::Initialize()
{
	Headlights::GetInstance()->Activate(false);
}

// Called repeatedly when this Command is scheduled to run
void HeadlightsOff::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool HeadlightsOff::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void HeadlightsOff::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HeadlightsOff::Interrupted()
{
	End();
}
