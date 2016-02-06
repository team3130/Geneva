#ifndef CLIMBER_H
#define CLIMBER_H

#include "Commands/Subsystem.h"
#include <WPILib.h>

class Climber: public Subsystem
{
private:
	static Climber* m_pInstance;
	Talon* m_climberWinchController;
	Talon* m_climberTapeController;
	Climber();

public:
	static Climber* GetInstance();
	void InitDefaultCommand();
	void MoveClimberTapes(float speed);
	void MoveClimberWinch(float speed);
};

#endif
