#ifndef DRIVE_STREIGHT_TEST_H
#define DRIVE_STREIGHT_TEST_H

#include <WPILib.h>

class DriveStreightTest: public Command
{
public:
	DriveStreightTest();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
