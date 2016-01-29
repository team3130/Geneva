#include <OI.h>
#include "Commands/ControlShooter.h"
#include "Subsystems/Shooter.h"


/// Default constructor of the class.
ControlShooterCommand::ControlShooterCommand()
{
	manualMode = true;
	preset = kX;
	buttonHold = false;
	Requires(ShooterSubsystem::GetInstance());
}

/// Called just before this Command runs the first time.
void ControlShooterCommand::Initialize()
{
	manualMode = true;
	buttonHold = false;
	ShooterSubsystem::GetInstance()->moveShooter(0);
}

//Passes 1 to shooter when the button is pressed, and 0 when it isn't
void ControlShooterCommand::Execute()
{
	OI* oi = OI::GetInstance();
	if(oi)
	{
		double thumb = -oi->gamepad->GetRawAxis(AXS_WINCH); // Y-axis is positive down.
		if(fabs(thumb) > 0.1)
		{
			manualMode = true;
			buttonHold = false;
			ShooterSubsystem::GetInstance()->moveShooter(thumb);
		}
		else {
			ShooterSubsystem::GetInstance()->moveShooter(0);
		}
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
	ShooterSubsystem::GetInstance()->moveShooter(0);
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void ControlShooterCommand::Interrupted()
{
	End();
}
