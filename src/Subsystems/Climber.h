#ifndef CLIMBER_H
#define CLIMBER_H

#include "Commands/Subsystem.h"
#include <WPILib.h>

class Climber: public Subsystem
{
private:
	static Climber* m_pInstance;
	Talon* m_climberController;
	Climber();

public:
	static Climber* GetInstance();
	void InitDefaultCommand();
	void MoveClimber(float speed);
};

#endif
