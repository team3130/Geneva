#include "Subsystems/Intake.h"
#include "Commands/ControlIntake.h"

Intake* Intake::m_pInstance = NULL;

Intake* Intake::GetInstance()
{
	if(!m_pInstance) m_pInstance = new Intake;
	return m_pInstance;
}

Intake::Intake() :
		Subsystem("Intake")
{
	m_intakeController = new Talon(PORT_INTAKEMOTOR);
	m_intakeActuater = new Solenoid(CAN_PNMMODULE, PNM_INTAKEACTUATE);
}

void Intake::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ControlIntake());
}

//Modifies the speed of the intake motor with the value speed
void Intake::SpinIntake(float speed)
{
	m_intakeController->Set(speed);
}

void Intake::Actuate(bool extended)
{
	m_intakeActuater->Set(extended);
}
