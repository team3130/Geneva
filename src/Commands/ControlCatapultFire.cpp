#include "OI.h"
#include "Subsystems/CatapultFire.h"
#include "Subsystems/IntakeHorizontal.h"
#include "Subsystems/Catapult.h"
#include "Commands/ControlCatapultFire.h"
#include "Commands/ReloadCatapult.h"
#include "Subsystems/Blinkies.h"

/// Default constructor of the class.
ControlCatapultFire::ControlCatapultFire(bool bypass)
	: m_nextCommand(new ReloadCatapult(BTN_PRESET_2))
	, timer(new Timer())
	, m_waiting(false)
	, m_bypass(bypass)
{
	Requires(CatapultFire::GetInstance());
	//Requires(IntakeHorizontal::GetInstance());
}

/// Called just before this Command runs the first time.
void ControlCatapultFire::Initialize()
{

		CatapultFire::GetInstance()->Actuate(false);
		if(IntakeHorizontal::GetInstance()->IsExtended() == false)
		{
			IntakeHorizontal::GetInstance()->Actuate(true);
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
	if((!m_waiting or timer->Get() > .25))
	{
		CatapultFire::GetInstance()->Actuate(OI::GetInstance()->stickR->GetTrigger());
		m_waiting = false;
	}

}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool ControlCatapultFire::IsFinished()
{
	if (m_bypass) return false;
	else if (timer->Get() > (m_waiting ? 0.5 : 0.25)) return not OI::GetInstance()->gamepad->GetRawButton(BTN_SHOOT);
	return false;
}

/// Called once after isFinished returns true
void ControlCatapultFire::End()
{
	CatapultFire::GetInstance()->Actuate(false);
	if(!m_waiting and timer->Get() < 3.0 && !m_bypass) m_nextCommand->Start();
	Blinkies::PutCommand("ballFired");
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void ControlCatapultFire::Interrupted()
{
	End();
}
