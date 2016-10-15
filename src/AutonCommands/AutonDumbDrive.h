#ifndef AUTON_DUMB_DRIVE_H
#define AUTON_DUMB_DRIVE_H

#include <WPILib.h>

class AutonDumbDrive: public Command
{
private:
	float m_speed;
	bool m_shiftLow;
public:
	AutonDumbDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetParam(float speed, bool shiftLow) {m_speed = speed; m_shiftLow = shiftLow;}
};

#endif
