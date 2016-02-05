#include "ControlClimber.h"
#include "Subsystems/Climber.h"
#include "OI.h"

ControlClimber::ControlClimber()
{
	Requires(Climber::GetInstance());
}

// Called just before this Command runs the first time
void ControlClimber::Initialize()
{
	Climber::GetInstance()->MoveClimber(0);
}

// Called repeatedly when this Command is scheduled to run
void ControlClimber::Execute()
{
	OI* oi = OI::GetInstance();

	if(oi->gamepad->GetRawButton(12))
	{
		Climber::GetInstance()->MoveClimber(1);
	}else if(oi->gamepad->GetRawButton(12)){
		Climber::GetInstance()->MoveClimber(-1);
	}else{
		Climber::GetInstance()->MoveClimber(0);
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
	Climber::GetInstance()->MoveClimber(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ControlClimber::Interrupted()
{
	End();
}
