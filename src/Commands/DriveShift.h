#ifndef DRIVE_SHIFT_H
#define DRIVE_SHIFT_H

#include <WPILib.h>

class DriveShift: public Command
{
public:
	DriveShift();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
