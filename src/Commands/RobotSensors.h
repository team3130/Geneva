#ifndef ROBOT_SENSORS_H
#define ROBOT_SENSORS_H

#include <WPILib.h>

class RobotSensors: public Command
{
private:
	BuiltInAccelerometer* accelerometer;
public:
	RobotSensors();
	~RobotSensors();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
