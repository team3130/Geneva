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
	m_climberWinchController->SetInverted(true);
	m_climberWinchController2->SetInverted(true);
	m_climberTapeController = new CANTalon(CAN_CLIMBERTAPE);
	LiveWindow::GetInstance()->AddActuator("Climber","Winch Talon",m_climberWinchController);
	LiveWindow::GetInstance()->AddActuator("Climber","Winch Talon 2",m_climberWinchController2);
	LiveWindow::GetInstance()->AddActuator("Climber","Tape Talon",m_climberTapeController);

	m_PWMclimberTapeController = new Talon(PORT_CLIMBERTAPE);
	m_PWMclimberWinchController = new Talon(PORT_CLIMBERWINCH);
	m_PWMclimberWinchController2 = new Talon(PORT_CLIMBERWINCH2);
	m_PWMclimberWinchController->SetInverted(true);
	m_PWMclimberWinchController2->SetInverted(true);
	LiveWindow::GetInstance()->AddActuator("Climber","PWM Winch Talon",m_PWMclimberWinchController);
	LiveWindow::GetInstance()->AddActuator("Climber","PWM Winch Talon 2",m_PWMclimberWinchController2);
	LiveWindow::GetInstance()->AddActuator("Climber","PWM Tape Talon",m_PWMclimberTapeController);
}

void Climber::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ControlClimber());
}

void Climber::MoveClimberTapes(float speed)
{
	m_climberTapeController->Set(speed);

	m_PWMclimberTapeController->Set(speed);
}

void Climber::MoveClimberWinch(float speed)
{
	m_climberWinchController->Set(speed);
	m_climberWinchController2->Set(speed);

	m_PWMclimberWinchController->Set(speed);
	m_PWMclimberWinchController2->Set(speed);
}

