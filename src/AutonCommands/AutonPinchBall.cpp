#include "AutonCommands/AutonPinchBall.h"
#include "Subsystems/Bincher.h"

AutonPinchBall::AutonPinchBall()
{
	timer = new Timer();

	m_timeout = 0;
	m_state = false;

	Requires(Bincher::GetInstance());
}

AutonPinchBall::~AutonPinchBall()
{
	delete timer;
}

// Called just before this Command runs the first time
void AutonPinchBall::Initialize()
{
	Bincher::GetInstance()->Actuate(m_state);
}

// Called repeatedly when this Command is scheduled to run
void AutonPinchBall::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool AutonPinchBall::IsFinished()
{
	return (timer->Get() > m_timeout);
}

// Called once after isFinished returns true
void AutonPinchBall::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonPinchBall::Interrupted()
{
	End();
}
