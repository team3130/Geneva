#include <Subsystems/Intake.h>
#include "Commands/ControlIntake.h"

IntakeSubsystem* IntakeSubsystem::m_pInstance = NULL;

IntakeSubsystem* IntakeSubsystem::GetInstance()
{
	if(!m_pInstance) m_pInstance = new IntakeSubsystem;
	return m_pInstance;
}

IntakeSubsystem::IntakeSubsystem() :
		Subsystem("Intake")
{
	m_intakeController = new Talon(INTAKEMOTOR);
}

void IntakeSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ControlIntakeCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void IntakeSubsystem::Intake(float speed)
{
	m_intakeController->Set(speed);
}
