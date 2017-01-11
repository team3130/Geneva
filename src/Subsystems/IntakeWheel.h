#ifndef INTAKE_WHEEL_H
#define INTAKE_WHEEL_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"
#include <CANTalon.h>

/** Robot's main chassis, or drivetrain.
 *
 * This must be a singleton class because a robot usually can have only one chassis.
 * The class manages all the driving motors and all methods of driving itself.
 * All activities with the drivetrain must be done via its public methods.
 */
class IntakeWheel: public Subsystem
{
private:
	static IntakeWheel* m_pInstance;
	CANTalon* m_intakeController;


	IntakeWheel();
	IntakeWheel(IntakeWheel const&);
	IntakeWheel& operator=(IntakeWheel const&);
public:
	static IntakeWheel* GetInstance();
	void InitDefaultCommand();
	void SpinIntake(float speed);
};

#endif
