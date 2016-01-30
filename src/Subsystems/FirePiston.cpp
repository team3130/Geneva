#include "Subsystems/FirePiston.h"
#include "Commands/ControlFirePiston.h"

FirePiston* FirePiston::m_pInstance = NULL;

FirePiston* FirePiston::GetInstance()
{
	if(!m_pInstance) m_pInstance = new FirePiston;
	return m_pInstance;
}

FirePiston::FirePiston() :
		Subsystem("FirePiston")
{
	m_intakeActuater = new Solenoid(CAN_PNMMODULE, PNM_SHOOTERLOCK);
}

void FirePiston::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ControlFirePiston());
}

void FirePiston::Actuate(bool released)
{
	m_intakeActuater->Set(released);
}
