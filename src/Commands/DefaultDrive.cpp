#include <Commands/DefaultDrive.h>
#include <Subsystems/Chassis.h>
#include <OI.h>

/// Default constructor of the class.
DefaultDriveCommand::DefaultDriveCommand()
{
	Requires(ChassisSubsystem::GetInstance());
}

/// Called just before this Command runs the first time.
void DefaultDriveCommand::Initialize()
{
}

//Pass values from joysticks to the Drive subsystem
void DefaultDriveCommand::Execute()
{
	OI* oi = OI::GetInstance();
	double moveSpeedL = oi->stickL->GetY();
	double moveSpeedR = oi->stickR->GetY();
	double speedMultiplier = (-0.5 * oi->stickL->GetZ()) + 0.5;
	double turnMultiplier = (-0.5 * oi->stickR->GetZ()) + 0.5;

	// Only driving manual should require Quadratic inputs. By default it should be turned off
	// Therefore here we turn it on explicitly.
	ChassisSubsystem::GetInstance()->Drive(moveSpeedL, moveSpeedR, true);
}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool DefaultDriveCommand::IsFinished()
{
	return false;
}

/// Called once after isFinished returns true
void DefaultDriveCommand::End()
{
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void DefaultDriveCommand::Interrupted()
{
}
