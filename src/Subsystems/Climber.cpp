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
	m_climberWinchController = new CANTalon(CAN_CLIMBERWINCH);
	m_climberTapeController = new CANTalon(CAN_CLIMBERTAPE);
}

void Climber::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ControlClimber());
}

void Climber::MoveClimberTapes(float speed)
{
	m_climberTapeController->Set(speed);
}

void Climber::MoveClimberWinch(float speed)
{
	m_climberWinchController->Set(speed);
}

