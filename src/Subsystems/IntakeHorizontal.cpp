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
	m_intakeActuater = new DoubleSolenoid(PNM_INTAKEACTUATEOUT,PNM_INTAEKACTUATEIN);
}


void IntakeHorizontal::InitDefaultCommand()
{
	SetDefaultCommand(new ControlIntakeHorizontal());
}

void IntakeHorizontal::Actuate(bool extended)
{
	if(extended){
		m_intakeActuater->Set(DoubleSolenoid::kForward);
	}else{
		m_intakeActuater->Set(DoubleSolenoid::kReverse);
	}

}
