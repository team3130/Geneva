#include "Headlights.h"
#include "../RobotMap.h"

Headlights* Headlights::m_pInstance = NULL;

Headlights* Headlights::GetInstance()
{
	if(!m_pInstance) m_pInstance = new Headlights;
	return m_pInstance;
}

Headlights::Headlights() :
		Subsystem("Headlights")
{
	m_relay = new Relay(3);
}

void Headlights::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Headlights::Activate(bool on)
{
	if (on) {
		m_relay->Set(Relay::Value::kForward);
	}
	else {
		m_relay->Set(Relay::Value::kOff);
	}
}
