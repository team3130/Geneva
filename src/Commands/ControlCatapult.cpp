#include "OI.h"
#include "Commands/ControlCatapult.h"
#include "Subsystems/Catapult.h"


/// Default constructor of the class.
ControlCatapult::ControlCatapult()
{
	manualMode = kSafe;
	Requires(Catapult::GetInstance());
}

/// Called just before this Command runs the first time.
void ControlCatapult::Initialize()
{
	manualMode = kSafe;
	Catapult::GetInstance()->moveCatapult(0);
	timer.Reset();
	timer.Start();
}

//Passes 1 to shooter when the button is pressed, and 0 when it isn't
void ControlCatapult::Execute()
{
	OI* oi = OI::GetInstance();
	Catapult* cat = Catapult::GetInstance();
	if(oi && cat)
	{
		double thumb = -oi->gamepad->GetRawAxis(AXS_WINCH); // Y-axis is positive down.
		bool danger = cat->WatchCurrent();
		if (danger or timer.Get() > 2.0) {
			timer.Reset();
			if (danger) {
				manualMode = thumb > 0 ? kOverloadUp : kOverloadDown;
			}
		}
		if((thumb > 0.1 and manualMode != kOverloadUp) or (thumb < -0.1 and manualMode != kOverloadDown))
		{
			cat->moveCatapult(thumb);
		}
		else {
			cat->moveCatapult(0);
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
