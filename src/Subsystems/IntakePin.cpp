#include "IntakePin.h"
#include "Commands/Pintake.h"
#include "../RobotMap.h"
#include "Misc/ToggleClass.h"

IntakePin* IntakePin::m_pInstance = NULL;

IntakePin* IntakePin::GetInstance()
{
	if(!m_pInstance) m_pInstance = new IntakePin;
	return m_pInstance;
}

IntakePin::IntakePin() :
		Subsystem("IntakePin")
{
	m_actuator = new Solenoid(CAN_PNMMODULE, PNM_INTAKEPIN);
	m_pinState = new Toggle<bool>(false,true);
	LiveWindow::GetInstance()->AddActuator("Intake", "Pin", m_actuator);
}

void IntakePin::InitDefaultCommand()
{
}

void IntakePin::Actuate(bool extended)
{
	m_actuator->Set(extended);
	m_pinState->setStatus(extended);
}

void IntakePin::ActuateToggle(bool Toggle)
{
	m_actuator->Set(m_pinState->toggleStatusOnEdgeChange(Toggle));
}
