#include "OI.h"
#include "Subsystems/ShooterMotor.h"
#include "Commands/ControlShooterMotor.h"


/// Default constructor of the class.
ControlShooterMotor::ControlShooterMotor()
{
	wheelSpeed = 0;
	preset = kX;
	Requires(ShooterMotor::GetInstance());
}

/// Called just before this Command runs the first time.
void ControlShooterMotor::Initialize()
{
	ShooterMotor::GetInstance()->SpinWheels(0);
	wheelSpeed = 0;
}

//Passes 1 to shooter when the button is pressed, and 0 when it isn't
void ControlShooterMotor::Execute()
{
	OI* oi = OI::GetInstance();
	if(oi)
	{
		//Allows control of shooter wheel speed by Face buttons and SMD
		if(oi->gamepad->GetRawButton(LST_BTN_B)){
			wheelSpeed = 0;
		}else if(oi->gamepad->GetRawButton(LST_BTN_X)){
			wheelSpeed = Preferences::GetInstance()->GetFloat("ShooterWheelSpeedX", 0.8);
		}else if(oi->gamepad->GetRawButton(LST_BTN_Y)){
			wheelSpeed = Preferences::GetInstance()->GetFloat("ShooterWheelSpeedY", 1.0);
		}else if(oi->gamepad->GetRawAxis(LST_AXS_LTRIGGER > 0)){ //Uses axis as a button
			wheelSpeed = Preferences::GetInstance()->GetFloat("ShooterWheelSpeedIntake", -0.8);
		}
		ShooterMotor::GetInstance()->SpinWheels(wheelSpeed);
	}
}

/// Make this return true when this Command no longer needs to run execute().
/// \return always false since this is the default command and should never finish.
bool ControlShooterMotor::IsFinished()
{
	return false;
}

/// Called once after isFinished returns true
void ControlShooterMotor::End()
{
	ShooterMotor::GetInstance()->SpinWheels(0);
}

/// Called when another command which requires one or more of the same
/// subsystems is scheduled to run
void ControlShooterMotor::Interrupted()
{
	End();
}
