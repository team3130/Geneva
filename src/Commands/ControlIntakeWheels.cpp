#include "OI.h"
#include "Commands/ControlIntakeWheels.h"
#include "Subsystems/IntakeWheel.h"
#include "Misc/ToggleClass.h"

/// Default constructor of the class.
ControlIntakeWheels::ControlIntakeWheels()
{
	IntakeArmPosition = new Toggle<bool>(false,true);
	Requires(IntakeWheel::GetInstance());
}

/// Called just before this Command runs the first time.
void ControlIntakeWheels::Initialize()
{
	IntakeWheel::GetInstance()->SpinIntake(0);
}


void ControlIntakeWheels::Execute()
{
	OI* oi = OI::GetInstance();

	//In and out control for the intake bar
	if(oi->gamepad->GetRawButton(BTN_INTAKE))
	{
		IntakeWheel::GetInstance()->SpinIntake(Preferences::GetInstance()->GetDouble("Intake Speed",1));
	}else if(oi->gamepad->GetRawButton(BTN_OUTAKE)){
		IntakeWheel::GetInstance()->SpinIntake(-Preferences::GetInstance()->GetDouble("Intake Speed",1));
	}else{
		IntakeWheel::GetInstance()->SpinIntake(0);
	}
}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool ControlIntakeWheels::IsFinished()
{
	return false;
}

/// Called once after isFinished returns true
void ControlIntakeWheels::End()
{
	IntakeWheel::GetInstance()->SpinIntake(0);
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void ControlIntakeWheels::Interrupted()
{
	End();
}
