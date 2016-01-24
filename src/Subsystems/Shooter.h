#ifndef SHOOTER_H
#define SHOOTER_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"

/** Robot's main chassis, or drivetrain.
 *
 * This must be a singleton class because a robot usually can have only one chassis.
 * The class manages all the driving motors and all methods of driving itself.
 * All activities with the drivetrain must be done via its public methods.
 */
class ShooterSubsystem: public Subsystem
{
private:
	static ShooterSubsystem* m_pInstance;
	Talon* m_shooterController;


	ShooterSubsystem();
	ShooterSubsystem(ShooterSubsystem const&);
	ShooterSubsystem& operator=(ShooterSubsystem const&);
public:
	static ShooterSubsystem* GetInstance();
	void InitDefaultCommand();
	void Shoot(float speed);
};

#endif
