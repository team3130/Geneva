#ifndef CLIMBER_H
#define CLIMBER_H

#include "Commands/Subsystem.h"
#include <WPILib.h>

class Climber: public Subsystem
{
private:
	static Climber* m_pInstance;
	CANTalon* m_climberTapeController;
	CANTalon* m_climberWinchController;
	CANTalon* m_climberWinchController2;

	Talon* m_PWMclimberTapeController;
	Talon* m_PWMclimberWinchController;
	Talon* m_PWMclimberWinchController2;

	Climber();

public:
	static Climber* GetInstance();
	void InitDefaultCommand();
	void MoveClimberTapes(float speed);
	void MoveClimberWinch(float speed);
};

#endif
