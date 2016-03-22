#include <OI.h>
#include "Subsystems/Catapult.h"
#include "ReloadCatapult.h"

ReloadCatapult::ReloadCatapult(uint32_t button, bool remote)
	: m_goal(0)
	, m_button(button)
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
	m_goal = Catapult::GetInstance()->GetPosition();
	m_buttonHold = true;
	m_goingDown = true;
	m_done = false;
	m_timer.Reset();
	m_timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void ReloadCatapult::Execute()
{
	if (m_buttonHold) {
		if (!OI::GetInstance()->gamepad->GetRawButton(m_button)) {
			// Only when the button released start doing stuff
			// or if the button never been pushed the timer will be ~0.0
			m_buttonHold = false;
			if (m_timer.Get() > 3.0) {
				if (m_goal > Catapult::SLOW_ZONE && m_goal < Catapult::TOP_ZONE) {
					Preferences::GetInstance()->PutDouble(m_presetLabel, m_goal);
					Catapult::GetInstance()->toSetpoint(m_goal);
					m_goingDown = false;
				}
			}
			else {
				Catapult::GetInstance()->moveCatapult(-0.75);
				m_goingDown = true;
			}
			m_timer.Reset();
		}
	}
	else {
		if (Catapult::GetInstance()->WatchCurrent() and m_timer.Get() > 0.2) {
			// If it's some time into moving watch for the current spike.
			Catapult::GetInstance()->moveCatapult(0);
			m_done = true;
		}

		if (m_goingDown){
			if (Catapult::GetInstance()->CheckZero()) {
				m_goingDown = false;
				Catapult::GetInstance()->toSetpoint(Preferences::GetInstance()->GetDouble(m_presetLabel, 8.8));
				m_timer.Reset();
			}
		}
		else {
			m_done = abs(Catapult::GetInstance()->GetPIDError()) < Preferences::GetInstance()->GetInt("WinchTolerance", 45);
		}
	}
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
	// If normal End() do nothing. Let the PID hold the position.
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReloadCatapult::Interrupted()
{
	// If interrupted for any reason stop the motor.
	Catapult::GetInstance()->moveCatapult(0);
}
