#include <OI.h>
#include "Commands/ControlShooter.h"
#include "Subsystems/Shooter.h"


/// Default constructor of the class.
ControlShooterCommand::ControlShooterCommand()
{
	manualMode = true;
	preset = kX;
	buttonHold = false;
	Requires(ShooterSubsystem::GetInstance());
}

/// Called just before this Command runs the first time.
void ControlShooterCommand::Initialize()
{
	manualMode = true;
	buttonHold = false;
	ShooterSubsystem::GetInstance()->moveShooter(0);
}

//Passes 1 to shooter when the button is pressed, and 0 when it isn't
void ControlShooterCommand::Execute()
{
	OI* oi = OI::GetInstance();
	if(oi)
	{
		const char * presetX = "WinchPositionX";
		const char * presetY = "WinchPositionY";
		const char *pref_preset = presetX;
		double thumb = oi->gamepad->GetRawAxis(AXS_WINCH);
		if(fabs(thumb) > 0.1)
		{
			manualMode = true;
			buttonHold = false;
			ShooterSubsystem::GetInstance()->moveShooter(oi->gamepad->GetRawAxis(AXS_WINCH));
		}else{
			bool buttonPushed = false;
			buttonPushed = false;
			if(oi->gamepad->GetRawButton(LST_BTN_X)){
				preset = kX;
				pref_preset = presetX;
				buttonPushed = true;
			}else if(oi->gamepad->GetRawButton(LST_BTN_Y)){
				preset = kY;
				pref_preset = presetY;
				buttonPushed = true;
			}


			if(buttonPushed){
				//go to a preset when a button is pushed
				manualMode = false;
				if(!buttonHold){
					buttonHold = true;
					timer.Reset();
					timer.Start();
				}
			}else{
				int goal = 0;
				switch(preset){
					case kX:
						pref_preset = presetX;
						goal = Preferences::GetInstance()->GetInt(pref_preset, 200);//TODO:Set real default value
						break;
					case kY:
						pref_preset = presetY;
						goal = Preferences::GetInstance()->GetInt(pref_preset, 400);//TODO:Set real default value
						break;
				}
				if(buttonHold && timer.Get() > 3){
					Preferences::GetInstance()->PutInt(pref_preset,ShooterSubsystem::GetInstance()->GetPosition());
				}else if(manualMode){
					//Do nothing if in manual mode and nothing has happened
					ShooterSubsystem::GetInstance()->moveShooter(0);
				}else{
					//if nothing else is happeneing, go to setpoint
					ShooterSubsystem::GetInstance()->readyShot(goal);
				}
				buttonHold = false;
			}
		}
	}
}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool ControlShooterCommand::IsFinished()
{
	return false;
}

/// Called once after isFinished returns true
void ControlShooterCommand::End()
{
	ShooterSubsystem::GetInstance()->moveShooter(0);
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void ControlShooterCommand::Interrupted()
{
	End();
}
