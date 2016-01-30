#ifndef SHOOTER_MOTOR_H
#define SHOOTER_MOTOR_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"

//The subsystem for the shooting mechanism for the robot

class ShooterMotor: public Subsystem
{
private:
	static ShooterMotor* m_pInstance;
	Talon* m_shooterController;

	ShooterMotor();
	ShooterMotor(ShooterMotor const&);
	ShooterMotor& operator=(ShooterMotor const&);
public:
	static ShooterMotor* GetInstance();
	void InitDefaultCommand();
	void SpinWheels(float speed);


};

#endif
