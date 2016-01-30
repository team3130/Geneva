#include "../RobotMap.h"
#include "Commands/ControlCatapult.h"
#include "Subsystems/Catapult.h"

Catapult* Catapult::m_pInstance = NULL;

Catapult* Catapult::GetInstance()
{
	if(!m_pInstance) m_pInstance = new Catapult;
	return m_pInstance;
}

Catapult::Catapult()
		:Subsystem("Catapult")
{
	m_shooterController = new Talon(PORT_SHOOTERWHEELMOTOR);
}

void Catapult::InitDefaultCommand()
{
	SetDefaultCommand(new ControlCatapult());
}



void Catapult::SpinWheels(float speed)
{
	m_shooterController->Set(speed);
}
