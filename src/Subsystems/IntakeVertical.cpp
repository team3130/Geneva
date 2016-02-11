#include "IntakeVertical.h"
#include "Commands/ControlIntakeVertical.h"

IntakeVertical* IntakeVertical::m_pInstance = NULL;

IntakeVertical* IntakeVertical::GetInstance()
{
	if(!m_pInstance) m_pInstance = new IntakeVertical;
	return m_pInstance;
}

IntakeVertical::IntakeVertical() :
		Subsystem("IntakeVertical")
{
	m_intakeActuater = new Solenoid(CAN_PNMMODULE, PNM_INTAKEACTUATEUP);
	LiveWindow::GetInstance()->AddActuator("Intake","Pivot/Vertical Solenoid",m_intakeActuater);
}


void IntakeVertical::InitDefaultCommand()
{
	SetDefaultCommand(new ControlIntakeVertical());
}

void IntakeVertical::Actuate(bool extended)
{
	m_intakeActuater->Set(extended);
}
