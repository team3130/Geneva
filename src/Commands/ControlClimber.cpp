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

	//Test if the pov is on the upper half of its range, but also pressed
	if(oi->gamepad->GetPOV() > LST_POV_W || (oi->gamepad->GetPOV() < LST_POV_E && oi->gamepad->GetPOV() >= LST_POV_N))
	{
		Climber::GetInstance()->MoveClimberTapes(0.4);
	//Test if the pov is in the lower half of its range
	}else if(oi->gamepad->GetPOV() > LST_POV_E && oi->gamepad->GetPOV() < LST_POV_W){
		Climber::GetInstance()->MoveClimberTapes(-0.2);
	}else{
		Climber::GetInstance()->MoveClimberTapes(0);
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
