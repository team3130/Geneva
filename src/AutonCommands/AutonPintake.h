#ifndef AUTON_PINTAKE_H
#define AUTON_PINTAKE_H

#include <WPILib.h>

class AutonPintake: public Command
{
private:
	Timer* timer;

	float m_timeout;
	bool m_state;
public:
	AutonPintake();
	~AutonPintake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetParam(float timeout, bool stateSet){
		m_timeout = timeout;
		m_state = stateSet;
	}
};

#endif
