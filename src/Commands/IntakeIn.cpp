#include "IntakeIn.h"
#include "Subsystems/IntakeHorizontal.h"
#include "Subsystems/IntakeVertical.h"
#include "Subsystems/IntakePin.h"

IntakeIn::IntakeIn()
{
	Requires(IntakeHorizontal::GetInstance());
	Requires(IntakePin::GetInstance());
	Requires(IntakeVertical::GetInstance());
}

// Called just before this Command runs the first time
void IntakeIn::Initialize()
{
	IntakeHorizontal::GetInstance()->Actuate(false);
	IntakeHorizontal::GetInstance()->Actuate(false);
	IntakePin::GetInstance()->Actuate(false);
}

// Called repeatedly when this Command is scheduled to run
void IntakeIn::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool IntakeIn::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void IntakeIn::End()
{
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeIn::Interrupted()
{

}
