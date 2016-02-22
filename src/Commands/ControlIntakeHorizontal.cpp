#include "OI.h"
#include "RobotMap.h"
#include "ControlIntakeHorizontal.h"
#include "Subsystems/IntakeHorizontal.h"
#include "Subsystems/IntakeVertical.h"
#include "Subsystems/IntakePin.h"
#include "Misc/ToggleClass.h"

#include <math.h>

ControlIntakeHorizontal::ControlIntakeHorizontal()
{
	Requires(IntakeHorizontal::GetInstance());
	IntakeArmPositionOut = new Toggle<bool>(false,true);
}

// Called just before this Command runs the first time
void ControlIntakeHorizontal::Initialize()
{
	IntakeHorizontal::GetInstance()->Actuate(false);

	IntakeArmPositionOut->setStatus(false);
}

// Called repeatedly when this Command is scheduled to run
void ControlIntakeHorizontal::Execute()
{
	OI* oi = OI::GetInstance();

	if(IntakeArmPositionOut->getStatus() && !IntakePin::GetInstance()->IsActive()
			&& IntakeVertical::GetInstance()->GetToggleState() && oi->gamepad->GetRawAxis(AXS_INTAKEHORIZONTAL > 0.1))
		{
			IntakeVertical::GetInstance()->Actuate(false);
			IntakeVertical::GetInstance()->SetState(false);
		}
	//Toggles actuator position on button press
	IntakeHorizontal::GetInstance()->Actuate(IntakeArmPositionOut->toggleStatusOnEdgeChange(fabs(oi->gamepad->GetRawAxis(AXS_INTAKEHORIZONTAL) > 0.1)));
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
