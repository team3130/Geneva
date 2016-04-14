#include "IntakeOut.h"
#include "Subsystems/IntakeHorizontal.h"

IntakeOut::IntakeOut()
{
	Requires(IntakeHorizontal::GetInstance());
}

// Called just before this Command runs the first time
void IntakeOut::Initialize()
{
	IntakeHorizontal::GetInstance()->Actuate(true);
}

// Called repeatedly when this Command is scheduled to run
void IntakeOut::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool IntakeOut::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void IntakeOut::End()
{
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeOut::Interrupted()
{

}
