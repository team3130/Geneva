#ifndef AUTON_PINTAKE_H
#define AUTON_PINTAKE_H

#include <WPILib.h>

class AutonPintake: public Command
{
private:
	bool m_state;
public:
	AutonPintake();
	~AutonPintake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetParam(bool stateSet){
		m_state = stateSet;
	}
};

#endif
