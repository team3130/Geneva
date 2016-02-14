#include "1BallAuton.h"

OneBallAuton::OneBallAuton()
{

}

OneBallAuton::~OneBallAuton()
{
}

// Called just before this Command runs the first time
void OneBallAuton::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void OneBallAuton::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool OneBallAuton::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void OneBallAuton::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OneBallAuton::Interrupted()
{
	End();
}
