#include "Commands/ControlIntakeWheels.h"
#include "Subsystems/IntakeWheel.h"

IntakeWheel* IntakeWheel::m_pInstance = NULL;

IntakeWheel* IntakeWheel::GetInstance()
{
	if(!m_pInstance) m_pInstance = new IntakeWheel;
	return m_pInstance;
}

IntakeWheel::IntakeWheel() :
		Subsystem("IntakeWheel")
{
	m_intakeController = new CANTalon(CAN_INTAKEMOTOR);
	LiveWindow::GetInstance()->AddActuator("Intake","Wheel Talon",m_intakeController);
}

void IntakeWheel::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ControlIntakeWheels());
}

//Modifies the speed of the intake motor with the value speed
void IntakeWheel::SpinIntake(float speed)
{
	m_intakeController->Set(speed);
}
