#include "../RobotMap.h"
#include "Subsystems/ShooterMotor.h"
#include "Commands/ControlShooterMotor.h"

ShooterMotor* ShooterMotor::m_pInstance = NULL;

ShooterMotor* ShooterMotor::GetInstance()
{
	if(!m_pInstance) m_pInstance = new ShooterMotor;
	return m_pInstance;
}

ShooterMotor::ShooterMotor()
		:Subsystem("ShooterMotor")
{
	m_shooterController = new Talon(PORT_SHOOTERWHEELMOTOR);
}

void ShooterMotor::InitDefaultCommand()
{
	SetDefaultCommand(new ControlShooterMotor());
}



void ShooterMotor::SpinWheels(float speed)
{
	m_shooterController->Set(speed);
}
