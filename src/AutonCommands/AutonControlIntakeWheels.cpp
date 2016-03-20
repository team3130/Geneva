#include "OI.h"
#include "AutonCommands/AutonControlIntakeWheels.h"
#include "Subsystems/IntakeWheel.h"
#include "Misc/ToggleClass.h"

/// Default constructor of the class.
AutonControlIntakeWheels::AutonControlIntakeWheels()
{
	m_Speed = 0;
	Requires(IntakeWheel::GetInstance());
}

AutonControlIntakeWheels::~AutonControlIntakeWheels()
{
}

/// Called just before this Command runs the first time.
void AutonControlIntakeWheels::Initialize()
{
	IntakeWheel::GetInstance()->SpinIntake(m_Speed);
}


void AutonControlIntakeWheels::Execute()
{

}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool AutonControlIntakeWheels::IsFinished()
{
	return false;
}

/// Called once after isFinished returns true
void AutonControlIntakeWheels::End()
{
	IntakeWheel::GetInstance()->SpinIntake(0);
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void AutonControlIntakeWheels::Interrupted()
{
	End();
}
