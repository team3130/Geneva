#include <OI.h>
#include "Commands/ControlIntake.h"
#include "Subsystems/Intake.h"
#include "Misc/ToggleClass.h"

/// Default constructor of the class.
ControlIntakeCommand::ControlIntakeCommand()
{
	IntakeArmPosition = new Toggle<bool>(false,true);
	Requires(IntakeSubsystem::GetInstance());
}

/// Called just before this Command runs the first time.
void ControlIntakeCommand::Initialize()
{
	IntakeSubsystem::GetInstance()->Intake(0);
	IntakeSubsystem::GetInstance()->Actuate(false);
}


void ControlIntakeCommand::Execute()
{
	OI* oi = OI::GetInstance();

	//In and out control for the intake bar
	if(oi->gamepad->GetRawButton(BTN_INTAKE))
	{
		IntakeSubsystem::GetInstance()->Intake(1);
	}else if(oi->gamepad->GetRawButton(BTN_OUTAKE)){
		IntakeSubsystem::GetInstance()->Intake(-1);
	}else{
		IntakeSubsystem::GetInstance()->Intake(0);
	}

	//Toggles actuator position on button press
	IntakeSubsystem::GetInstance()->Actuate(IntakeArmPosition->toggleStatusOnEdgeChange(oi->gamepad->GetRawButton(BTN_ACTUATE)));
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
	IntakeSubsystem::GetInstance()->Actuate(false);
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void ControlIntakeCommand::Interrupted()
{
	End();
}
