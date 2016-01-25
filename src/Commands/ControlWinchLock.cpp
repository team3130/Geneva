#include <OI.h>
#include "Commands/ControlWinchLock.h"
#include "Subsystems/WinchLock.h"

/// Default constructor of the class.
ControlWinchLockCommand::ControlWinchLockCommand()
{
	Requires(WinchLockSubsystem::GetInstance());
}

/// Called just before this Command runs the first time.
void ControlWinchLockCommand::Initialize()
{
	WinchLockSubsystem::GetInstance()->Actuate(false);
}


void ControlWinchLockCommand::Execute()
{
	OI* oi = OI::GetInstance();
	WinchLockSubsystem::GetInstance()->Actuate(oi->stickL->GetRawButton(BTN_LEFTSHOOT) && oi->stickR->GetRawButton(BTN_RIGHTSHOOT));
	WinchLockSubsystem::GetInstance()->moveWinch(oi->gamepad->GetRawAxis(0));
}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool ControlWinchLockCommand::IsFinished()
{
	return false;
}

/// Called once after isFinished returns true
void ControlWinchLockCommand::End()
{
	WinchLockSubsystem::GetInstance()->Actuate(false);
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void ControlWinchLockCommand::Interrupted()
{
	End();
}
