#include "AutonCommands/AutonControlIntakeVertical.h"
#include "OI.h"
#include "Subsystems/IntakeVertical.h"
#include "Misc/ToggleClass.h"

AutonControlIntakeVertical::AutonControlIntakeVertical()
{
	Requires(IntakeVertical::GetInstance());
	m_TimeOut = 0;
	m_bExtend = false;
	timer = new Timer();
}

AutonControlIntakeVertical::~AutonControlIntakeVertical()
{
delete timer;

}

// Called just before this Command runs the first time
void AutonControlIntakeVertical::Initialize()
{

	timer->Reset();
	timer->Start();
	IntakeVertical::GetInstance()->Actuate(m_bExtend);
}

// Called repeatedly when this Command is scheduled to run
void AutonControlIntakeVertical::Execute()
{


	//Toggles actuator position on button press
}

// Make this return true when this Command no longer needs to run execute()
bool AutonControlIntakeVertical::IsFinished()
{
	return (timer->Get() > m_TimeOut);
}

// Called once after isFinished returns true
void AutonControlIntakeVertical::End()
{


}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonControlIntakeVertical::Interrupted()
{

}
