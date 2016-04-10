#ifndef CDFACTUATE_H
#define CDFACTUATE_H

#include <WPILib.h>

class CDFActuate: public Command
{
public:
	CDFActuate();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
