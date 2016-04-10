#include "PortcullisActuate.h"
#include "Subsystems/IntakeHorizontal.h"
#include "Subsystems/IntakeVertical.h"
#include "Subsystems/IntakePin.h"

PortcullisActuate::PortcullisActuate()
{
	Requires(IntakeHorizontal::GetInstance());
	Requires(IntakePin::GetInstance());
	Requires(IntakeVertical::GetInstance());
}

// Called just before this Command runs the first time
void PortcullisActuate::Initialize()
{
	IntakeHorizontal::GetInstance()->Actuate(true);
	IntakePin::GetInstance()->Actuate(true);
}

// Called repeatedly when this Command is scheduled to run
void PortcullisActuate::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool PortcullisActuate::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void PortcullisActuate::End()
{
	IntakeHorizontal::GetInstance()->Actuate(false);
	IntakeVertical::GetInstance()->Actuate(false);
	IntakePin::GetInstance()->Actuate(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PortcullisActuate::Interrupted()
{

}
