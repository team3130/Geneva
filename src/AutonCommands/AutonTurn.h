#ifndef AUTON_TURN_H
#define AUTON_TURN_H

#include <WPILib.h>

class AutonTurn: public Command
{
private:
	float m_angle;
public:
	AutonTurn();
	~AutonTurn();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetParam(float angle){m_angle = angle;}
};

#endif
