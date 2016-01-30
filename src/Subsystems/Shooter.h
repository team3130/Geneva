#ifndef SHOOTER_H
#define SHOOTER_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"

//The subsystem for the shooting mechanism for the robot

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
	void SpinWheels(float speed);

};

#endif
