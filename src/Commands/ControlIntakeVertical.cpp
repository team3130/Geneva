#include "OI.h"
#include "ControlIntakeVertical.h"
#include "Subsystems/IntakeVertical.h"
#include "Misc/ToggleClass.h"

ControlIntakeVertical::ControlIntakeVertical()
{
	Requires(IntakeVertical::GetInstance());
	IntakeArmPositionUp = new Toggle<bool>(false,true);
}

// Called just before this Command runs the first time
void ControlIntakeVertical::Initialize()
{
	IntakeVertical::GetInstance()->Actuate(false);
}

// Called repeatedly when this Command is scheduled to run
void ControlIntakeVertical::Execute()
{
	OI* oi = OI::GetInstance();

	//Toggles actuator position on button press
	IntakeVertical::GetInstance()->Actuate(IntakeArmPositionUp->toggleStatusOnEdgeChange(oi->gamepad->GetRawButton(LST_BTN_LBUMPER)));
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
