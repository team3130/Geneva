#include "PinchBall.h"
#include "Subsystems/Bincher.h"

PinchBall::PinchBall()
{
	Requires(Bincher::GetInstance());
}

// Called just before this Command runs the first time
void PinchBall::Initialize()
{
	Bincher::GetInstance()->Actuate(true);
}

// Called repeatedly when this Command is scheduled to run
void PinchBall::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool PinchBall::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void PinchBall::End()
{
	Bincher::GetInstance()->Actuate(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PinchBall::Interrupted()
{
	End();
}
