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
class Intake: public Subsystem
{
private:
	static Intake* m_pInstance;
	Talon* m_intakeController;
	Solenoid* m_intakeActuater;


	Intake();
	Intake(Intake const&);
	Intake& operator=(Intake const&);
public:
	static Intake* GetInstance();
	void InitDefaultCommand();
	void SpinIntake(float speed);
	void Actuate(bool extended);
};

#endif
