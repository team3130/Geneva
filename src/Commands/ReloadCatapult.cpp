#include <OI.h>
#include "Subsystems/Catapult.h"
#include "ReloadCatapult.h"

ReloadCatapult::ReloadCatapult(uint32_t button, bool remote)
	: m_button(button)
	, m_buttonHold(false)
	, m_goingDown(true)
	, m_done(false)
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
	m_goingDown = true;
	m_done = false;
	m_timer.Reset();
	m_timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void ReloadCatapult::Execute()
{
	OI* oi = OI::GetInstance();
	if(oi) {
		if (m_buttonHold) {
			if (!oi->gamepad->GetRawButton(m_button)) {
				// Only when the button released start doing stuff
				// or if the button never been pushed the timer will be ~0.0
				m_buttonHold = false;
				double goal = Catapult::GetInstance()->GetPosition();
				if (m_timer.Get() > 3.0 && goal > Catapult::SLOW_ZONE && goal < Catapult::TOP_ZONE) {
					Preferences::GetInstance()->PutDouble(m_presetLabel, goal);
					Catapult::GetInstance()->toSetpoint(goal);
					m_goingDown = false;
					m_timer.Reset();
				}
				else {
					Catapult::GetInstance()->moveCatapult(-0.75);
					m_goingDown = true;
				}
			}
		}
		else if (m_goingDown){
			if (Catapult::GetInstance()->CheckZero() or Catapult::GetInstance()->WatchCurrent()) {
				m_goingDown = false;
				float goal = Preferences::GetInstance()->GetDouble(m_presetLabel, 10);
				Catapult::GetInstance()->toSetpoint(goal);
				m_timer.Reset();
			}
		}
		else if (m_timer.Get() > 0.2) {
			if (Catapult::GetInstance()->WatchCurrent()) {
				// If it's some time on the way up watch for the current spike.
				Catapult::GetInstance()->moveCatapult(0);
				m_done = true;
			}
			else m_done = abs(Catapult::GetInstance()->GetPIDError()) < Preferences::GetInstance()->GetInt("WinchTolerance", 4);
		}
		// "else" it's just waiting for the timer doing nothing
	}
	else m_done = true;
}

// Make this return true when this Command no longer needs to run execute()
bool ReloadCatapult::IsFinished()
{
	if (OI::GetInstance()->gamepad->GetRawAxis(AXS_WINCH) > 0.1) return true;
	return m_done;
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
