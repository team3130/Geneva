#include "Subsystems/Chassis.h"
#include "Commands/DefaultDrive.h"

Chassis* Chassis::m_pInstance = NULL;

Chassis* Chassis::GetInstance()
{
	if(!m_pInstance) m_pInstance = new Chassis;
	return m_pInstance;
}

Chassis::Chassis() :
		Subsystem("Chassis")
{
	m_drive = new RobotDrive(CAN_LEFTMOTOR,CAN_RIGHTMOTOR);
	m_drive->SetSafetyEnabled(false);
	m_shifter = new Solenoid(PNM_GEARSHIFTER);
	m_leftMotor = new CANTalon(CAN_LEFTMOTOR);
	m_rightMotor = new CANTalon(CAN_RIGHTMOTOR);
	m_bShiftedLow = false;

	LiveWindow::GetInstance()->AddActuator("Chassis","Left TalonSRX",m_leftMotor);
	LiveWindow::GetInstance()->AddActuator("Chassis","Right TalonSRX",m_rightMotor);
	LiveWindow::GetInstance()->AddActuator("Chassis","Gear Shift Solenoid",m_shifter);

}

void Chassis::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new DefaultDrive());
}

//Arcade Drives with the values of move as the forward value, and turn as the turning value
void Chassis::Drive(double moveL, double moveR, bool quad)
{
	m_drive->TankDrive(moveL, moveR, quad);
}

void Chassis::Shift(bool shiftDown)
{
	m_shifter->Set(shiftDown);
	m_bShiftedLow = shiftDown;
}
