#ifndef PINTAKE_H
#define PINTAKE_H

#include <WPILib.h>

class Pintake: public Command
{
public:
	Pintake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
