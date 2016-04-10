#ifndef PORTCULLISACTUATE_H
#define PORTCULLISACTUATE_H

#include <WPILib.h>

class PortcullisActuate: public Command
{
public:
	PortcullisActuate();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
