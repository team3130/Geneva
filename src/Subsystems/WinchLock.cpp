#include "Subsystems/WinchLock.h"
#include "Commands/ControlWinchLock.h"

WinchLockSubsystem* WinchLockSubsystem::m_pInstance = NULL;

WinchLockSubsystem* WinchLockSubsystem::GetInstance()
{
	if(!m_pInstance) m_pInstance = new WinchLockSubsystem;
	return m_pInstance;
}

WinchLockSubsystem::WinchLockSubsystem() :
		Subsystem("WinchLock")
{
	m_intakeActuater = new Solenoid(PNM_MODULE, PNM_SHOOTERLOCK);
}

void WinchLockSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ControlWinchLockCommand());
}

void WinchLockSubsystem::Actuate(bool released)
{
	m_intakeActuater->Set(released);
}
