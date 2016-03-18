#ifndef DRIVE_SHIFT_UP_H
#define DRIVE_SHIFT_UP_H

#include <WPILib.h>

class DriveShiftUp: public Command
{
public:
	DriveShiftUp();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
