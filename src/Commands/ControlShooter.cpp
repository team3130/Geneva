#include <OI.h>
#include "Commands/ControlShooter.h"
#include "Subsystems/Shooter.h"


/// Default constructor of the class.
ControlShooterCommand::ControlShooterCommand()
{
	preset = kX;
	Requires(ShooterSubsystem::GetInstance());
}

/// Called just before this Command runs the first time.
void ControlShooterCommand::Initialize()
{
	ShooterSubsystem::GetInstance()->SpinWheels(0);
	wheelSpeed = 0;
}

//Passes 1 to shooter when the button is pressed, and 0 when it isn't
void ControlShooterCommand::Execute()
{
	OI* oi = OI::GetInstance();
	if(oi)
	{
		if(oi->gamepad->GetRawButton(LST_BTN_A)){
			wheelSpeed = 0;
		}else if(oi->gamepad->GetRawButton(LST_BTN_B)){
			wheelSpeed = 0.7;
		}else if(oi->gamepad->GetRawButton(LST_BTN_X)){
			wheelSpeed = 0.8;
		}else if(oi->gamepad->GetRawButton(LST_BTN_Y)){
			wheelSpeed = 1;
		}
		ShooterSubsystem::GetInstance()->SpinWheels(wheelSpeed);
	}
}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool ControlShooterCommand::IsFinished()
{
	return false;
}

/// Called once after isFinished returns true
void ControlShooterCommand::End()
{
	ShooterSubsystem::GetInstance()->SpinWheels(0);
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void ControlShooterCommand::Interrupted()
{
	End();
}
