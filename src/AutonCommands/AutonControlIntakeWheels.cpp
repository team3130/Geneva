#include "OI.h"
#include "AutonCommands/AutonControlIntakeWheels.h"
#include "Subsystems/IntakeWheel.h"
#include "Misc/ToggleClass.h"

/// Default constructor of the class.
AutonControlIntakeWheels::AutonControlIntakeWheels()
{
	m_Speed = 0;
	m_TimeOut = 0;
	timer = new Timer();
	Requires(IntakeWheel::GetInstance());
}

AutonControlIntakeWheels::~AutonControlIntakeWheels()
{
	delete timer;
}

/// Called just before this Command runs the first time.
void AutonControlIntakeWheels::Initialize()
{
	timer->Reset();
	timer->Start();
	IntakeWheel::GetInstance()->SpinIntake(m_Speed);
}


void AutonControlIntakeWheels::Execute()
{

}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool AutonControlIntakeWheels::IsFinished()
{
	return (timer->Get() > m_TimeOut);
}

/// Called once after isFinished returns true
void AutonControlIntakeWheels::End()
{
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void AutonControlIntakeWheels::Interrupted()
{
	End();
}
