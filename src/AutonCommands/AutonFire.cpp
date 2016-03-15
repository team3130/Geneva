#include "Subsystems/CatapultFire.h"
#include "Subsystems/IntakeVertical.h"
#include "Subsystems/Bincher.h"
#include "AutonCommands/AutonFire.h"

/// Default constructor of the class.
AutonFire::AutonFire()
{
	timer = new Timer();
	m_waiting = false;

	m_timeout = 0;

	Requires(CatapultFire::GetInstance());
	Requires(IntakeVertical::GetInstance());
	Requires(Bincher::GetInstance());
}

AutonFire::~AutonFire()
{
	delete timer;
}

/// Called just before this Command runs the first time.
void AutonFire::Initialize()
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


void AutonFire::Execute()
{
	if(!m_waiting or timer->Get() > .25)
	{
		CatapultFire::GetInstance()->Actuate(true);
	}

}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool AutonFire::IsFinished()
{
	return CatapultFire::GetInstance()->GetState();
}

/// Called once after isFinished returns true
void AutonFire::End()
{
	CatapultFire::GetInstance()->Actuate(false);
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void AutonFire::Interrupted()
{
	// Do not call the normal End(); We don't want to start the next command if we're interrupted.
	CatapultFire::GetInstance()->Actuate(false);
}
