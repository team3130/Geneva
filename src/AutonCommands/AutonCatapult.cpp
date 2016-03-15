#include "AutonCommands/AutonCatapult.h"
#include "Subsystems/Catapult.h"

AutonCatapult::AutonCatapult()
{

	m_setpoint = 0;
	m_threshold = 0;

	Requires(Catapult::GetInstance());
}

AutonCatapult::~AutonCatapult()
{

}

// Called just before this Command runs the first time
void AutonCatapult::Initialize()
{
	Catapult::GetInstance()->moveCatapult(-1.0);
}

// Called repeatedly when this Command is scheduled to run
void AutonCatapult::Execute()
{
	if(Catapult::GetInstance()->CheckZero()) {
		Catapult::GetInstance()->toSetpoint(m_setpoint);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutonCatapult::IsFinished()
{
	return (Catapult::GetInstance()->GetPosition() < m_setpoint+m_threshold
			&& Catapult::GetInstance()->GetPosition() > m_setpoint-m_threshold);
}

// Called once after isFinished returns true
void AutonCatapult::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonCatapult::Interrupted()
{

}
