#include "AutonCommands/AutonTurn.h"
#include "Subsystems/Chassis.h"

AutonTurn::AutonTurn()
{
	m_angle = 0;
	modeTwo = false;
}

AutonTurn::~AutonTurn()
{
}

// Called just before this Command runs the first time
void AutonTurn::Initialize()
{
	Chassis::GetInstance()->SetGyroMode(true);
	if(modeTwo)  Chassis::GetInstance()->HoldAngle(m_angle - Chassis::GetInstance()->GetAngle(),true);
	else  Chassis::GetInstance()->HoldAngle(m_angle, true);
	Chassis::GetInstance()->SetAbsoluteTolerance(0.5);		//Unit Tolerance
	Chassis::GetInstance()->DriveStraight(0);
}

// Called repeatedly when this Command is scheduled to run
void AutonTurn::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool AutonTurn::IsFinished()
{
	return Chassis::GetInstance()->OnTarget();
}

// Called once after isFinished returns true
void AutonTurn::End()
{
	Chassis::GetInstance()->ReleaseAngle();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonTurn::Interrupted()
{

}
