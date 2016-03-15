#ifndef CATAPULT_FIRE_H
#define CATAPULT_FIRE_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"

/** Robot's main chassis, or drivetrain.
 *
 * This must be a singleton class because a robot usually can have only one chassis.
 * The class manages all the driving motors and all methods of driving itself.
 * All activities with the drivetrain must be done via its public methods.
 */
class CatapultFire: public Subsystem
{
private:
	static CatapultFire* m_pInstance;
	Solenoid* m_intakeActuater;


	CatapultFire();
	CatapultFire(CatapultFire const&);
	CatapultFire& operator=(CatapultFire const&);
public:
	static CatapultFire* GetInstance();
	void InitDefaultCommand();
	void Actuate(bool extended);
	bool GetState(){return m_intakeActuater->Get();}
};

#endif
