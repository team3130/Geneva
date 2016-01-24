#include <Subsystems/Chassis.h>
#include "Commands/DefaultDrive.h"

ChassisSubsystem* ChassisSubsystem::m_pInstance = NULL;

ChassisSubsystem* ChassisSubsystem::GetInstance()
{
	if(!m_pInstance) m_pInstance = new ChassisSubsystem;
	return m_pInstance;
}

ChassisSubsystem::ChassisSubsystem() :
		Subsystem("Chassis")
{
	m_drive = new RobotDrive(PORT_LEFTMOTOR,PORT_RIGHTMOTOR);
	m_drive->SetSafetyEnabled(false);

	// Inverted motors for TurboMoose wiring only.
	/*
	m_drive->SetInvertedMotor(RobotDrive::kFrontLeftMotor,true);
	m_drive->SetInvertedMotor(RobotDrive::kFrontRightMotor,true);
	m_drive->SetInvertedMotor(RobotDrive::kRearLeftMotor,true);
	m_drive->SetInvertedMotor(RobotDrive::kRearRightMotor,true);
	*/
}

void ChassisSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new DefaultDriveCommand());
}

//Arcade Drives with the values of move as the forward value, and turn as the turning value
void ChassisSubsystem::Drive(double moveL, double moveR, bool quad)
{
	m_drive->TankDrive(moveL, moveR, quad);
}
