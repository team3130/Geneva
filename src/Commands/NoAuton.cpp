#include "NoAuton.h"

NoAuton::NoAuton()
{

}

NoAuton::~NoAuton()
{
}

// Called just before this Command runs the first time
void NoAuton::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void NoAuton::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool NoAuton::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void NoAuton::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void NoAuton::Interrupted()
{
	End();
}
