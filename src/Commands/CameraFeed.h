#ifndef CameraFeed_H
#define CameraFeed_H

#include "WPILib.h"

class CameraFeed: public Command
{
	Image *image;
public:
	CameraFeed();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
