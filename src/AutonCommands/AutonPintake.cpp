#include "AutonCommands/AutonPintake.h"
#include "Subsystems/Bincher.h"

AutonPintake::AutonPintake()
{
	timer = new Timer();

	m_timeout = 0;
	m_state = false;

	Requires(Bincher::GetInstance());
}

AutonPintake::~AutonPintake()
{
	delete timer;
}

// Called just before this Command runs the first time
void AutonPintake::Initialize()
{
	timer->Reset();
	timer->Start();

	Bincher::GetInstance()->Actuate(m_state);
}

// Called repeatedly when this Command is scheduled to run
void AutonPintake::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool AutonPintake::IsFinished()
{
	return (timer->Get() > m_timeout);
}

// Called once after isFinished returns true
void AutonPintake::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonPintake::Interrupted()
{
	End();
}
