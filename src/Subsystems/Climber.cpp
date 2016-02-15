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
	m_climberWinchController2 = new CANTalon(CAN_CLIMBERWINCH2);
	m_climberTapeController = new CANTalon(CAN_CLIMBERTAPE);
	LiveWindow::GetInstance()->AddActuator("Climber","Winch Talon",m_climberWinchController);
	LiveWindow::GetInstance()->AddActuator("Climber","Winch Talon 2",m_climberWinchController2);
	LiveWindow::GetInstance()->AddActuator("Climber","Tape Talon",m_climberTapeController);
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
	m_climberWinchController2->Set(speed);
}

