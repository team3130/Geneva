#include "OI.h"
#include "Subsystems/CatapultFire.h"
#include "Subsystems/IntakeVertical.h"
#include "Commands/ControlCatapultFire.h"

/// Default constructor of the class.
ControlCatapultFire::ControlCatapultFire()
{
	Requires(CatapultFire::GetInstance());
	Requires(IntakeVertical::GetInstance());
	timer = new Timer();
}

/// Called just before this Command runs the first time.
void ControlCatapultFire::Initialize()
{
	CatapultFire::GetInstance()->Actuate(false);
	timer->Stop();
	timer->Reset();
}


void ControlCatapultFire::Execute()
{
	OI* oi = OI::GetInstance();
	if(oi->gamepad->GetRawButton(BTN_SHOOT))
	{
		IntakeVertical::GetInstance()->Actuate(false);
		IntakeVertical::GetInstance()->ToggleStateManual(false);
		timer->Start();
	}
	if(timer->Get() > .5)
	{
		CatapultFire::GetInstance()->Actuate(true);
		timer->Stop();
		timer->Reset();
	}

}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool ControlCatapultFire::IsFinished()
{
	return false;
}

/// Called once after isFinished returns true
void ControlCatapultFire::End()
{
	CatapultFire::GetInstance()->Actuate(false);
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void ControlCatapultFire::Interrupted()
{
	End();
}
