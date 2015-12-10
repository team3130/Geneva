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
        , m_drive(LEFTFRONTMOTOR,LEFTBACKMOTOR,RIGHTFRONTMOTOR,RIGHTBACKMOTOR)
{

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
	m_drive.ArcadeDrive(move, turn, quad);
}
