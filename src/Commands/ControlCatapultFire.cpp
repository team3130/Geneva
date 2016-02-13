#include "OI.h"
#include "Subsystems/CatapultFire.h"
#include "Subsystems/IntakeVertical.h"
#include "Subsystems/Bincher.h"
#include "Commands/ControlCatapultFire.h"

/// Default constructor of the class.
ControlCatapultFire::ControlCatapultFire()
{
	Requires(CatapultFire::GetInstance());
	Requires(IntakeVertical::GetInstance());
	Requires(Bincher::GetInstance());
	timer = new Timer();
	m_waiting = false;
}

/// Called just before this Command runs the first time.
void ControlCatapultFire::Initialize()
{
	CatapultFire::GetInstance()->Actuate(false);
	if(IntakeVertical::GetInstance()->GetToggleState() == false or Bincher::GetInstance()->IsActive())
	{
		IntakeVertical::GetInstance()->Actuate(true);
		Bincher::GetInstance()->Actuate(false);
		m_waiting = true;
	}
	else {
		m_waiting = false;
	}
	timer->Reset();
	timer->Start();
}


void ControlCatapultFire::Execute()
{
	if(!m_waiting or timer->Get() > .25)
	{
		CatapultFire::GetInstance()->Actuate(true);
	}

}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool ControlCatapultFire::IsFinished()
{
	return not OI::GetInstance()->gamepad->GetRawButton(BTN_SHOOT);
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
