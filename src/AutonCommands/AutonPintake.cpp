#include "AutonCommands/AutonPintake.h"
#include "Subsystems/IntakePin.h"

AutonPintake::AutonPintake()
{
	m_state = false;

	Requires(IntakePin::GetInstance());
}

AutonPintake::~AutonPintake()
{
}

// Called just before this Command runs the first time
void AutonPintake::Initialize()
{

	IntakePin::GetInstance()->Actuate(m_state);
}

// Called repeatedly when this Command is scheduled to run
void AutonPintake::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool AutonPintake::IsFinished()
{
	return false;
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
