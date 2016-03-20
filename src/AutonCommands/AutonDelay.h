#ifndef AUTON_DELAY_H
#define AUTON_DELAY_H

#include <WPILib.h>

class AutonDelay: public Command
{
private:

	Timer* timer;
	float m_delay;

public:
	AutonDelay();
	~AutonDelay();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void setParam(float delay){m_delay = delay;}
};

#endif
