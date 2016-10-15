#ifndef AUTON_DUMB_DRIVE_H
#define AUTON_DUMB_DRIVE_H

#include <WPILib.h>

class AutonDumbDrive: public Command
{
private:
	float m_speed;
public:
	AutonDumbDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetParam(float speed) {m_speed = speed;}
};

#endif
