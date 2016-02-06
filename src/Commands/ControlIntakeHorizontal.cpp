#include "OI.h"
#include "ControlIntakeHorizontal.h"
#include "Subsystems/IntakeHorizontal.h"
#include "Misc/ToggleClass.h"

ControlIntakeHorizontal::ControlIntakeHorizontal()
{
	Requires(IntakeHorizontal::GetInstance());
	IntakeArmPositionOut = new Toggle<bool>(false,true);
}

// Called just before this Command runs the first time
void ControlIntakeHorizontal::Initialize()
{
	IntakeHorizontal::GetInstance()->Actuate(false);
}

// Called repeatedly when this Command is scheduled to run
void ControlIntakeHorizontal::Execute()
{
	OI* oi = OI::GetInstance();

	//Toggles actuator position on button press
	IntakeHorizontal::GetInstance()->Actuate(IntakeArmPositionOut->toggleStatusOnEdgeChange(oi->gamepad->GetRawAxis(AXS_INTAKEHORIZONTAL) > 0.9));
}

// Make this return true when this Command no longer needs to run execute()
bool ControlIntakeHorizontal::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ControlIntakeHorizontal::End()
{
	IntakeHorizontal::GetInstance()->Actuate(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ControlIntakeHorizontal::Interrupted()
{

}
