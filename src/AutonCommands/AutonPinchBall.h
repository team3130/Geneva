#ifndef AUTON_PINCH_BALL_H
#define AUTON_PINCH_BALL_H

#include <WPILib.h>

class AutonPinchBall: public Command
{
private:
	Timer* timer;

	float m_timeout;
	bool m_state;
public:
	AutonPinchBall();
	~AutonPinchBall();
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
