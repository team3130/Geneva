#include "AutonCommands/AutonDelay.h"
#include "OI.h"
#include "RobotMap.h"
#include "Subsystems/IntakeHorizontal.h"

#include <math.h>

AutonDelay::AutonDelay()
{
	timer = new Timer();
	m_delay = 0;
}

AutonDelay::~AutonDelay()
{
	delete timer;
}

// Called just before this Command runs the first time
void AutonDelay::Initialize()
{
	timer->Stop();
	timer->Reset();
	timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void AutonDelay::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool AutonDelay::IsFinished()
{
	return (timer->Get() > m_delay);
}

// Called once after isFinished returns true
void AutonDelay::End()
{
	timer->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonDelay::Interrupted()
{

}
