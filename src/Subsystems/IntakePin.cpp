#include "Misc/RiptideRecorder/RiptideRecorder.h"

#include "IntakePin.h"
#include "../RobotMap.h"

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
	LiveWindow::GetInstance()->AddActuator("Intake", "Pin", m_actuator);

	Recorder::GetInstance()->AddDevice("IntakePin Solenoid",m_actuator);
}

void IntakePin::InitDefaultCommand()
{
}

void IntakePin::Actuate(bool extended)
{
	m_actuator->Set(extended);
}
