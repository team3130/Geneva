#include <OI.h>
#include "Commands/ControlIntake.h"
#include "Subsystems/Intake.h"
#include "../Misc/ToggleClass.h"

/// Default constructor of the class.
ControlIntakeCommand::ControlIntakeCommand()
{
	Requires(IntakeSubsystem::GetInstance());
}

/// Called just before this Command runs the first time.
void ControlIntakeCommand::Initialize()
{
	IntakeSubsystem::GetInstance()->Intake(0);
}

//Passes 1 to intake when the button is pressed, and 0 when it isn't
void ControlIntakeCommand::Execute()
{
	OI* oi = OI::GetInstance();
	if(oi->gamepad->GetRawButton(1))
	{
		IntakeSubsystem::GetInstance()->Intake(1);
	}else{
		IntakeSubsystem::GetInstance()->Intake(0);
	}
}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool ControlIntakeCommand::IsFinished()
{
	return false;
}

/// Called once after isFinished returns true
void ControlIntakeCommand::End()
{
	IntakeSubsystem::GetInstance()->Intake(0);
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void ControlIntakeCommand::Interrupted()
{
	End();
}
