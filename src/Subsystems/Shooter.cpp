#include "Shooter.h"
#include "../RobotMap.h"
#include "Subsystems/Shooter.h"
#include "Commands/ControlShooter.h"

ShooterSubsystem* ShooterSubsystem::m_pInstance = NULL;

ShooterSubsystem* ShooterSubsystem::GetInstance()
{
	if(!m_pInstance) m_pInstance = new ShooterSubsystem;
	return m_pInstance;
}

ShooterSubsystem::ShooterSubsystem():Subsystem("WheelyShooter")
{
	m_shooterController = new Talon(PORT_SHOOTERWHEELMOTOR);
}

void ShooterSubsystem::InitDefaultCommand()
{
	SetDefaultCommand(new ControlShooterCommand);
}


void ShooterSubsystem::SpinWheels(float speed)
{
	m_shooterController->Set(speed);
}
