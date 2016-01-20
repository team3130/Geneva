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
	m_drive = new RobotDrive(LEFTFRONTMOTOR,LEFTBACKMOTOR,RIGHTFRONTMOTOR,RIGHTBACKMOTOR);
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

// Put methods for controlling this subsystem
// here. Call these from Commands.

void ChassisSubsystem::Drive(double move, double turn, bool quad)
{
	m_drive->ArcadeDrive(move, turn, quad);
}
