#include "IntakeHorizontal.h"
#include "Commands/ControlIntakeHorizontal.h"

IntakeHorizontal* IntakeHorizontal::m_pInstance = NULL;

IntakeHorizontal* IntakeHorizontal::GetInstance()
{
	if(!m_pInstance) m_pInstance = new IntakeHorizontal;
	return m_pInstance;
}

IntakeHorizontal::IntakeHorizontal() :
		Subsystem("IntakeHorizontal")
{
	m_intakeActuater = new Solenoid(CAN_PNMMODULE, PNM_INTAKEACTUATEOUT);
}


void IntakeHorizontal::InitDefaultCommand()
{
	SetDefaultCommand(new ControlIntakeHorizontal());
}

void IntakeHorizontal::Actuate(bool extended)
{
	m_intakeActuater->Set(extended);
}
