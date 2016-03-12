#ifndef AUTON_CATAPULT_H
#define AUTON_CATAPULT_H

#include <WPILib.h>

class AutonCatapult: public Command
{
private:

	float m_setpoint;
	float m_threshold;
public:
	AutonCatapult();
	~AutonCatapult();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetParam(float stopAngle, float thresh){
		m_setpoint = stopAngle;
		m_threshold = thresh;
	}
};

#endif
