#ifndef AUTON_CATAPULT_H
#define AUTON_CATAPULT_H

#include <WPILib.h>

class AutonCatapult: public Command
{
private:
	Timer* timer;

	float m_setpoint;
	float m_timeout;
	float m_threshold;
public:
	AutonCatapult();
	~AutonCatapult();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetParam(float stopAngle, float thresh, float timeout){
		m_setpoint = stopAngle;
		m_threshold = thresh;
		m_timeout = timeout;
	}
};

#endif
