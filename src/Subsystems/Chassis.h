#ifndef CHASSIS_H
#define CHASSIS_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"

/** Robot's main chassis, or drivetrain.
 *
 * This must be a singleton class because a robot usually can have only one chassis.
 * The class manages all the driving motors and all methods of driving itself.
 * All activities with the drivetrain must be done via its public methods.
 */
class Chassis: public Subsystem
{
private:
	static Chassis* m_pInstance;
	RobotDrive *m_drive;

	Chassis();
	Chassis(Chassis const&);
	Chassis& operator=(Chassis const&);
public:
	static Chassis* GetInstance();
	void InitDefaultCommand();
	void Drive(double move, double turn, bool squaredInputs = false);
};

#endif
