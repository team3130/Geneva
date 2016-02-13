#include "Bincher.h"
#include "../RobotMap.h"

Bincher* Bincher::m_pInstance = NULL;

Bincher* Bincher::GetInstance()
{
	if(!m_pInstance) m_pInstance = new Bincher;
	return m_pInstance;
}

Bincher::Bincher() :
		Subsystem("Bincher")
{
	m_actuator = new Solenoid(CAN_PNMMODULE, PNM_BINCHER);
}

void Bincher::InitDefaultCommand()
{
}

void Bincher::Actuate(bool extended)
{
	m_actuator->Set(extended);
}
