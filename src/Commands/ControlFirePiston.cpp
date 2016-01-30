#include "OI.h"
#include "Commands/ControlFirePiston.h"
#include "Subsystems/FirePiston.h"

/// Default constructor of the class.
ControlFirePiston::ControlFirePiston()
{
	Requires(FirePiston::GetInstance());
}

/// Called just before this Command runs the first time.
void ControlFirePiston::Initialize()
{
	FirePiston::GetInstance()->Actuate(false);
}


void ControlFirePiston::Execute()
{
	OI* oi = OI::GetInstance();
	FirePiston::GetInstance()->Actuate(oi->gamepad->GetRawButton(LST_BTN_RBUMPER));
}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool ControlFirePiston::IsFinished()
{
	return false;
}

/// Called once after isFinished returns true
void ControlFirePiston::End()
{
	FirePiston::GetInstance()->Actuate(false);
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void ControlFirePiston::Interrupted()
{
	End();
}
