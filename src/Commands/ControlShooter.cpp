#include <Commands/ControlShooter.h>
#include <Subsystems/Shooter.h>
#include <OI.h>

/// Default constructor of the class.
ControlShooterCommand::ControlShooterCommand()
{
	Requires(ShooterSubsystem::GetInstance());
}

/// Called just before this Command runs the first time.
void ControlShooterCommand::Initialize()
{
	ShooterSubsystem::GetInstance()->Shoot(0);
}

/// Called repeatedly when this Command is scheduled to run.
void ControlShooterCommand::Execute()
{
	OI* oi = OI::GetInstance();
	if(oi->gamepad->GetRawButton(2))
	{
		ShooterSubsystem::GetInstance()->Shoot(1);
	}else{
		ShooterSubsystem::GetInstance()->Shoot(0);
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
	ShooterSubsystem::GetInstance()->Shoot(0);
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void ControlShooterCommand::Interrupted()
{
	End();
}
