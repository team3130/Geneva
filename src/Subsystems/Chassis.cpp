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
	m_leftMotorFront = new CANTalon(CAN_LEFTMOTORFRONT);
	m_leftMotorRear = new CANTalon(CAN_LEFTMOTORREAR);
	m_rightMotorFront = new CANTalon(CAN_RIGHTMOTORFRONT);
	m_rightMotorRear = new CANTalon(CAN_RIGHTMOTORREAR);
	m_drive = new RobotDrive(m_leftMotorFront, m_leftMotorRear, m_rightMotorFront, m_rightMotorRear);
	m_drive->SetSafetyEnabled(false);
	m_shifter = new Solenoid(PNM_GEARSHIFTER);
	m_bShiftedLow = false;
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
