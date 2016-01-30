#include "OI.h"
#include "Commands/ControlIntake.h"
#include "Subsystems/Intake.h"
#include "Misc/ToggleClass.h"

/// Default constructor of the class.
ControlIntake::ControlIntake()
{
	IntakeArmPosition = new Toggle<bool>(false,true);
	Requires(Intake::GetInstance());
}

/// Called just before this Command runs the first time.
void ControlIntake::Initialize()
{
	Intake::GetInstance()->SpinIntake(0);
	Intake::GetInstance()->Actuate(false);
}


void ControlIntake::Execute()
{
	OI* oi = OI::GetInstance();

	//In and out control for the intake bar
	if(oi->gamepad->GetRawButton(BTN_INTAKE))
	{
		Intake::GetInstance()->SpinIntake(1);
	}else if(oi->gamepad->GetRawButton(BTN_OUTAKE)){
		Intake::GetInstance()->SpinIntake(-1);
	}else{
		Intake::GetInstance()->SpinIntake(0);
	}

	//Toggles actuator position on button press
	Intake::GetInstance()->Actuate(IntakeArmPosition->toggleStatusOnEdgeChange(oi->gamepad->GetRawButton(BTN_GRAB)));
}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool ControlIntake::IsFinished()
{
	return false;
}

/// Called once after isFinished returns true
void ControlIntake::End()
{
	Intake::GetInstance()->SpinIntake(0);
	Intake::GetInstance()->Actuate(false);
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void ControlIntake::Interrupted()
{
	End();
}
