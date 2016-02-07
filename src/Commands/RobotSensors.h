#ifndef ROBOT_SENSORS_H
#define ROBOT_SENSORS_H

#include <WPILib.h>

class RobotSensors: public Command
{
public:
	LiveWindow* lw;
	RobotSensors();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
