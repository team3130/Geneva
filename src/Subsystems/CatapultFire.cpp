#include "Subsystems/CatapultFire.h"
#include "Commands/ControlCatapultFire.h"

CatapultFire* CatapultFire::m_pInstance = NULL;

CatapultFire* CatapultFire::GetInstance()
{
	if(!m_pInstance) m_pInstance = new CatapultFire;
	return m_pInstance;
}

CatapultFire::CatapultFire() :
		Subsystem("CatapultFire")
{
	m_intakeActuater = new Solenoid(CAN_PNMMODULE, PNM_SHOOTERLOCK);
}

void CatapultFire::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ControlCatapultFire());
}

void CatapultFire::Actuate(bool released)
{
	m_intakeActuater->Set(released);
}
