#include "RobotSensors.h"
#include "Subsystems/Catapult.h"
#include "OI.h"

RobotSensors::RobotSensors()
{
	this->SetRunWhenDisabled(true);
	lw = LiveWindow::GetInstance();
}

// Called just before this Command runs the first time
void RobotSensors::Initialize()
{
	Talon* intake_WheelTalon = new Talon(PORT_INTAKEMOTOR);
	lw->AddActuator("Intake","Wheel Talon",intake_WheelTalon);

	Solenoid* intake_VerticalSolenoid = new Solenoid(PNM_INTAKEACTUATEUP);
	lw->AddActuator("Intake","Pivot Solenoid", intake_VerticalSolenoid);

	Solenoid* intake_HorizontalSolenoid = new Solenoid(PNM_INTAKEACTUATEOUT);
	lw->AddActuator("Intake","Horizontal Solenoid", intake_HorizontalSolenoid);

	Talon* climber_TapeTalon = new Talon(PORT_CLIMBERTAPE);
	lw->AddActuator("Climber","Tape Talon",climber_TapeTalon);

	Talon* climber_WinchTalon = new Talon(PORT_CLIMBERWINCH);
	lw->AddActuator("Climber","Winch Talon", climber_WinchTalon);

	Talon* chassis_LeftTalon = new Talon(PORT_LEFTMOTOR);
	lw->AddActuator("Chassis","Left Talon", chassis_LeftTalon);

	Talon* chassis_RightTalon = new Talon(PORT_RIGHTMOTOR);
	lw->AddActuator("Chassis","Right Talon", chassis_RightTalon);

	Solenoid* chassis_GearSolenoid = new Solenoid(PNM_GEARSHIFTER);
	lw->AddActuator("Chassis","Gear Shifter Solenoid",chassis_GearSolenoid);

	Solenoid* catapultFire_FireSolenoid = new Solenoid(PNM_SHOOTERLOCK);
	lw->AddActuator("Catapult","Firing Solenoid",catapultFire_FireSolenoid);

	CANTalon* catapult_WinchTalon = new CANTalon(CAN_SHOOTERMOTOR);
	lw->AddActuator("Catapult","Winch Talon",catapult_WinchTalon);
}

// Called repeatedly when this Command is scheduled to run
void RobotSensors::Execute()
{
	SmartDashboard::PutBoolean("Shooter Lower Limit",Catapult::GetInstance()->isBottomHit());
	SmartDashboard::PutNumber("Shooter Position",Catapult::GetInstance()->GetPosition());
	SmartDashboard::PutNumber("POV Angles",OI::GetInstance()->gamepad->GetPOV());
}

// Make this return true when this Command no longer needs to run execute()
bool RobotSensors::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RobotSensors::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RobotSensors::Interrupted()
{

}
