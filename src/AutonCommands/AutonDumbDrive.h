#ifndef AUTON_DUMB_DRIVE_H
#define AUTON_DUMB_DRIVE_H

#include <WPILib.h>

class AutonDumbDrive: public Command
{
private:
	float m_speed;
	float m_timeDrive;
	bool m_shiftLow;
	Timer* timer;
public:
	AutonDumbDrive();
	~AutonDumbDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetParam(float time, float speed, bool shiftLow);
};

#endif
