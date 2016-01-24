#ifndef WINCH_LOCK_H
#define WINCH_LOCK_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"

/** Robot's main chassis, or drivetrain.
 *
 * This must be a singleton class because a robot usually can have only one chassis.
 * The class manages all the driving motors and all methods of driving itself.
 * All activities with the drivetrain must be done via its public methods.
 */
class WinchLockSubsystem: public Subsystem
{
private:
	static WinchLockSubsystem* m_pInstance;
	Solenoid* m_intakeActuater;


	WinchLockSubsystem();
	WinchLockSubsystem(WinchLockSubsystem const&);
	WinchLockSubsystem& operator=(WinchLockSubsystem const&);
public:
	static WinchLockSubsystem* GetInstance();
	void InitDefaultCommand();
	void WinchLock(float speed);
	void Actuate(bool extended);
};

#endif
