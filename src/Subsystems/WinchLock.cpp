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
	m_intakeActuater = new Solenoid(PNM_SHOOTERLOCK);
	m_winchTalon = new Talon(PORT_WINCHMOTOR);
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

void WinchLockSubsystem::moveWinch(float speedWinch)
{
	m_winchTalon->Set(speedWinch);
}
