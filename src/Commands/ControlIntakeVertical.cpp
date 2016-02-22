#include "OI.h"
#include "ControlIntakeVertical.h"
#include "Subsystems/IntakeHorizontal.h"
#include "Subsystems/IntakePin.h"
#include "Subsystems/IntakeVertical.h"
#include "Misc/ToggleClass.h"

ControlIntakeVertical::ControlIntakeVertical()
{
	Requires(IntakeVertical::GetInstance());
}

// Called just before this Command runs the first time
void ControlIntakeVertical::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ControlIntakeVertical::Execute()
{
	OI* oi = OI::GetInstance();

	//Toggles actuator position on button press
	if(!IntakePin::GetInstance()->IsActive() && !IntakeHorizontal::GetInstance()->IsExtended() &&
			!IntakeVertical::GetInstance()->GetToggleState() && oi->gamepad->GetRawButton(BTN_INTAKEVERTICAL))
	{
		IntakeHorizontal::GetInstance()->Actuate(true);
		IntakeVertical::GetInstance()->Actuate(true);
		IntakeVertical::GetInstance()->SetState(true);
	}else{
		IntakeVertical::GetInstance()->ActuateToggle(oi->gamepad->GetRawButton(BTN_INTAKEVERTICAL));
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ControlIntakeVertical::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ControlIntakeVertical::End()
{
	IntakeVertical::GetInstance()->Actuate(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ControlIntakeVertical::Interrupted()
{

}
