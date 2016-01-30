#ifndef CATAPULT_H
#define CATAPULT_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"

//The subsystem for the shooting mechanism for the robot

class Catapult: public Subsystem
{
private:
	static Catapult* m_pInstance;
	Talon* m_shooterController;

	Catapult();
	Catapult(Catapult const&);
	Catapult& operator=(Catapult const&);
public:
	static Catapult* GetInstance();
	void InitDefaultCommand();
	void SpinWheels(float speed);


};

#endif
