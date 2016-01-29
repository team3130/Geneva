#include "ReloadCatapult.h"
#include "Subsystems/Shooter.h"
#include "OI.h"

ReloadCatapult::ReloadCatapult(uint32_t button)
	: m_button(button)
	, m_buttonHold(false)
	, m_goingUp(false)
	, m_timer()
{
	Requires(ShooterSubsystem::GetInstance());
}

// Called just before this Command runs the first time
void ReloadCatapult::Initialize()
{
	ShooterSubsystem::GetInstance()->moveShooter(0);
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
		char presetLabel[] = "WinchPositionA";
		presetLabel[13] = 'A' + m_button;
		if (m_buttonHold) {
			if (oi->gamepad->GetRawButton(m_button)) {
				// If still held do nothing
			}
			else {
				m_buttonHold = false;
				if (m_timer.Get() > 3.0) {
					int goal = ShooterSubsystem::GetInstance()->GetPosition();
					Preferences::GetInstance()->PutInt(presetLabel, goal);
					ShooterSubsystem::GetInstance()->toSetpoint(goal);
					m_goingUp = true;
					m_timer.Reset();
				}
				else {
					ShooterSubsystem::GetInstance()->moveShooter(-1.0);
					m_goingUp = false;
				}
			}
		}
		else {
			if (ShooterSubsystem::GetInstance()->CheckZero()) {
				m_goingUp = true;
				int goal = Preferences::GetInstance()->GetInt(presetLabel, 2000);
				ShooterSubsystem::GetInstance()->toSetpoint(goal);
				m_timer.Reset();
			}
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ReloadCatapult::IsFinished()
{
	if (m_goingUp && m_timer.Get() > 0.2 && abs(ShooterSubsystem::GetInstance()->GetPIDError()) < 40) return true;
	if (OI::GetInstance()->gamepad->GetRawAxis(AXS_WINCH) > 0.1) return true;
	return false;
}

// Called once after isFinished returns true
void ReloadCatapult::End()
{
	//ShooterSubsystem::GetInstance()->moveShooter(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReloadCatapult::Interrupted()
{
	End();
}
