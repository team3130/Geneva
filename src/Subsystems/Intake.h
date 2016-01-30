#ifndef INTAKE_H
#define INTAKE_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"

/** Robot's main chassis, or drivetrain.
 *
 * This must be a singleton class because a robot usually can have only one chassis.
 * The class manages all the driving motors and all methods of driving itself.
 * All activities with the drivetrain must be done via its public methods.
 */
class IntakeSubsystem: public Subsystem
{
private:
	static IntakeSubsystem* m_pInstance;
	Talon* m_intakeController;
	Solenoid* m_intakeActuater;


	IntakeSubsystem();
	IntakeSubsystem(IntakeSubsystem const&);
	IntakeSubsystem& operator=(IntakeSubsystem const&);
public:
	static IntakeSubsystem* GetInstance();
	void InitDefaultCommand();
	void SpinIntake(float speed);
	void Actuate(bool extended);
};

#endif
