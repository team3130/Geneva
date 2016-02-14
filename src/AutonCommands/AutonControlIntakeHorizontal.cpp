#include "AutonCommands/AutonControlIntakeHorizontal.h"
#include "OI.h"
#include "RobotMap.h"
#include "Subsystems/IntakeHorizontal.h"
#include "Misc/ToggleClass.h"

#include <math.h>

AutonControlIntakeHorizontal::AutonControlIntakeHorizontal()
{
	Requires(IntakeHorizontal::GetInstance());
	m_TimeOut = 0;
	m_bExtend = false;
	timer = new Timer();

}

AutonControlIntakeHorizontal::~AutonControlIntakeHorizontal()
{
delete timer;

}

// Called just before this Command runs the first time
void AutonControlIntakeHorizontal::Initialize()
{

	timer->Reset();
	timer->Start();
	IntakeHorizontal::GetInstance()->Actuate(m_bExtend);



}

// Called repeatedly when this Command is scheduled to run
void AutonControlIntakeHorizontal::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool AutonControlIntakeHorizontal::IsFinished()
{
	return (timer->Get() > m_TimeOut);
}

// Called once after isFinished returns true
void AutonControlIntakeHorizontal::End()
{
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonControlIntakeHorizontal::Interrupted()
{

}
