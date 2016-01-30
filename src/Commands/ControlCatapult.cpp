#include "OI.h"
#include "Commands/ControlCatapult.h"
#include "Subsystems/Catapult.h"


/// Default constructor of the class.
ControlCatapult::ControlCatapult()
{
	manualMode = true;
	preset = kX;
	buttonHold = false;
	Requires(Catapult::GetInstance());
}

/// Called just before this Command runs the first time.
void ControlCatapult::Initialize()
{
	manualMode = true;
	buttonHold = false;
	Catapult::GetInstance()->moveCatapult(0);
}

//Passes 1 to shooter when the button is pressed, and 0 when it isn't
void ControlCatapult::Execute()
{
	OI* oi = OI::GetInstance();
	if(oi)
	{
		double thumb = -oi->gamepad->GetRawAxis(AXS_WINCH); // Y-axis is positive down.
		if(fabs(thumb) > 0.1)
		{
			manualMode = true;
			buttonHold = false;
			Catapult::GetInstance()->moveCatapult(thumb);
		}
		else {
			Catapult::GetInstance()->moveCatapult(0);
		}
	}
}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool ControlCatapult::IsFinished()
{
	return false;
}

/// Called once after isFinished returns true
void ControlCatapult::End()
{
	Catapult::GetInstance()->moveCatapult(0);
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void ControlCatapult::Interrupted()
{
	End();
}
