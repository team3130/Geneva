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
	m_drive = new RobotDrive(PORT_LEFTMOTOR,PORT_RIGHTMOTOR);
	m_drive->SetSafetyEnabled(false);
	m_shifter = new Solenoid(PNM_GEARSHIFTER);
	m_bShiftedLow = false;

	// Inverted motors for TurboMoose wiring only.
	/*
	m_drive->SetInvertedMotor(RobotDrive::kFrontLeftMotor,true);
	m_drive->SetInvertedMotor(RobotDrive::kFrontRightMotor,true);
	m_drive->SetInvertedMotor(RobotDrive::kRearLeftMotor,true);
	m_drive->SetInvertedMotor(RobotDrive::kRearRightMotor,true);
	*/
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
