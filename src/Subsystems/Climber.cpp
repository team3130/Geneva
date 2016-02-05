#include "Climber.h"
#include "../RobotMap.h"
#include "Commands/ControlClimber.h"

Climber* Climber::m_pInstance = NULL;

Climber* Climber::GetInstance()
{
	if(!m_pInstance) m_pInstance = new Climber;
	return m_pInstance;
}

Climber::Climber() :
		Subsystem("Climber")
{
	m_climberController = new Talon(PORT_CLIMBERMOTOR);
}

void Climber::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ControlClimber());
}

void Climber::MoveClimber(float speed)
{
	m_climberController->Set(speed);
}

