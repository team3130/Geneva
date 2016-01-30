#include "OI.h"
#include "Commands/DefaultDrive.h"
#include "Subsystems/Chassis.h"


/// Default constructor of the class.
DefaultDrive::DefaultDrive()
{
	Requires(Chassis::GetInstance());
}

/// Called just before this Command runs the first time.
void DefaultDrive::Initialize()
{
}

//Pass values from joysticks to the Drive subsystem
void DefaultDrive::Execute()
{
	OI* oi = OI::GetInstance();
	double moveSpeedL = oi->stickL->GetY();
	double moveSpeedR = oi->stickR->GetY();
	//double speedMultiplier = (-0.5 * oi->stickL->GetZ()) + 0.5;
	//double turnMultiplier = (-0.5 * oi->stickR->GetZ()) + 0.5;

	// Only driving manual should require Quadratic inputs. By default it should be turned off
	// Therefore here we turn it on explicitly.
	Chassis::GetInstance()->Drive(moveSpeedL, moveSpeedR, true);
}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool DefaultDrive::IsFinished()
{
	return false;
}

/// Called once after isFinished returns true
void DefaultDrive::End()
{
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void DefaultDrive::Interrupted()
{
}
