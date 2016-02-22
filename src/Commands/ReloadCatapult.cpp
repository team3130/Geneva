#include <OI.h>
#include "Subsystems/Catapult.h"
#include "ReloadCatapult.h"

ReloadCatapult::ReloadCatapult(uint32_t button, bool remote=false)
	: m_remote(remote)
	, m_button(button)
	, m_buttonHold(false)
	, m_goingUp(false)
	, m_timer()
{
	Requires(Catapult::GetInstance());
	strncpy(m_presetLabel, STR_PRESET, sizeof(STR_PRESET));
	m_presetLabel[sizeof(STR_PRESET)-2] = 'A' + m_button;
}

// Called just before this Command runs the first time
void ReloadCatapult::Initialize()
{
	Catapult::GetInstance()->moveCatapult(0);
	m_buttonHold = true;
	m_goingUp = false;
	m_timer.Reset();
	m_timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void ReloadCatapult::Execute()
{
	OI* oi = OI::GetInstance();
	if(oi) {
		if (m_buttonHold) {
			if (!oi->gamepad->GetRawButton(m_button) || m_remote) {
				// Only when the button released start doing stuff
				// or if the button never been pushed the timer will be ~0.0
				m_buttonHold = false;
				double goal = Catapult::GetInstance()->GetPosition();
				if (m_timer.Get() > 3.0 && goal > 2 && goal < Catapult::GetInstance()->TOP_ZONE) {
					Preferences::GetInstance()->PutDouble(m_presetLabel, goal);
					Catapult::GetInstance()->toSetpoint(goal);
					m_goingUp = true;
					m_timer.Reset();
				}
				else {
					Catapult::GetInstance()->moveCatapult(-1.0);
					m_goingUp = false;
				}
			}
		}
		else if (!m_goingUp){
			if (Catapult::GetInstance()->CheckZero()) {
				m_goingUp = true;
				float goal = Preferences::GetInstance()->GetDouble(m_presetLabel, 10);
				Catapult::GetInstance()->toSetpoint(goal);
				m_timer.Reset();
			}
		}else if(Catapult::GetInstance()->WatchCurrent()){
			Catapult::GetInstance()->moveCatapult(0);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ReloadCatapult::IsFinished()
{
	if (m_goingUp && m_timer.Get() > 0.2 && abs(Catapult::GetInstance()->GetPIDError()) < 0.1) return true;
	if (OI::GetInstance()->gamepad->GetRawAxis(AXS_WINCH) > 0.1) return true;
	return false;
}

// Called once after isFinished returns true
void ReloadCatapult::End()
{
	//Catapult::GetInstance()->moveCatapult(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReloadCatapult::Interrupted()
{
	End();
}
