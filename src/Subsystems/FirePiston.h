#ifndef FIRE_PISTON_H
#define FIRE_PISTON_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"

/** Robot's main chassis, or drivetrain.
 *
 * This must be a singleton class because a robot usually can have only one chassis.
 * The class manages all the driving motors and all methods of driving itself.
 * All activities with the drivetrain must be done via its public methods.
 */
class FirePiston: public Subsystem
{
private:
	static FirePiston* m_pInstance;
	Solenoid* m_intakeActuater;


	FirePiston();
	FirePiston(FirePiston const&);
	FirePiston& operator=(FirePiston const&);
public:
	static FirePiston* GetInstance();
	void InitDefaultCommand();
	void Actuate(bool extended);
};

#endif
