#include "ControlClimber.h"
#include "Subsystems/Climber.h"
#include "RobotMap.h"
#include "OI.h"

ControlClimber::ControlClimber()
{
	Requires(Climber::GetInstance());
}

// Called just before this Command runs the first time
void ControlClimber::Initialize()
{
	Climber::GetInstance()->MoveClimberTapes(0);
	Climber::GetInstance()->MoveClimberWinch(0);
}

// Called repeatedly when this Command is scheduled to run
void ControlClimber::Execute()
{
	OI* oi = OI::GetInstance();

	Climber::GetInstance()->MoveClimberTapes(Preferences::GetInstance()->GetDouble("TapesSpeed",0.5) * oi->gamepad->GetRawAxis(AXS_CLIMBERTAPES));

	if (oi->stickL->GetRawButton(9)) {
		Climber::GetInstance()->MoveClimberWinch(Preferences::GetInstance()->GetFloat("ClimbSpeed",-1));
	}else if(false)
	{
		Climber::GetInstance()->MoveClimberWinch(0.5);
	} else {
		Climber::GetInstance()->MoveClimberWinch(0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ControlClimber::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ControlClimber::End()
{
	Climber::GetInstance()->MoveClimberTapes(0);
	Climber::GetInstance()->MoveClimberWinch(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ControlClimber::Interrupted()
{
	End();
}
