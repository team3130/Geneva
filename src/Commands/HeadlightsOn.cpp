#include "HeadlightsOn.h"
#include "Subsystems/Headlights.h"

HeadlightsOn::HeadlightsOn()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Headlights::GetInstance());
}

// Called just before this Command runs the first time
void HeadlightsOn::Initialize()
{
	Headlights::GetInstance()->Activate(true);
}

// Called repeatedly when this Command is scheduled to run
void HeadlightsOn::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool HeadlightsOn::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void HeadlightsOn::End()
{
	Headlights::GetInstance()->Activate(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HeadlightsOn::Interrupted()
{
	End();
}
