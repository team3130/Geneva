#include <Subsystems/Shooter.h>
#include "Commands/ControlShooter.h"

ShooterSubsystem* ShooterSubsystem::m_pInstance = NULL;

ShooterSubsystem* ShooterSubsystem::GetInstance()
{
	if(!m_pInstance) m_pInstance = new ShooterSubsystem;
	return m_pInstance;
}

ShooterSubsystem::ShooterSubsystem() :
		Subsystem("Shooter")
{
	m_shooterController = new Talon(SHOOTERMOTOR);
}

void ShooterSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ControlShooterCommand());
}

//Modifies the shooter wheel speed with the value speed
void ShooterSubsystem::Shoot(float speed)
{
	m_shooterController->Set(speed);
}
