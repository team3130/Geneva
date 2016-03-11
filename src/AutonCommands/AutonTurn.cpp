#include "AutonCommands/AutonTurn.h"
#include "Subsystems/Chassis.h"

AutonTurn::AutonTurn()
{
	m_angle = 0;
}

AutonTurn::~AutonTurn()
{
}

// Called just before this Command runs the first time
void AutonTurn::Initialize()
{
	Chassis::GetInstance()->Drive(0,0);
	Chassis::GetInstance()->HoldAngle(m_angle);
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
