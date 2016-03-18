#ifndef DRIVE_SHIFT_DOWN_H
#define DRIVE_SHIFT_DOWN_H

#include <WPILib.h>

class DriveShiftDown: public Command
{
public:
	DriveShiftDown();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
