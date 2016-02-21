#include "Misc/RiptideRecorder/RiptideRecorder.h"

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

	Recorder::GetInstance()->AddDevice("Bincher Solenoid",m_actuator);
}

void Bincher::InitDefaultCommand()
{
}

void Bincher::Actuate(bool extended)
{
	m_actuator->Set(extended);
}
