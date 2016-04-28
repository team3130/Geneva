#ifndef Headlights_H
#define Headlights_H

#include "Commands/Subsystem.h"
#include "Relay.h"
#include "WPILib.h"

class Headlights: public Subsystem
{
private:
	static Headlights* m_pInstance;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Relay *m_relay;
	Headlights();
public:
	static Headlights* GetInstance();

	void InitDefaultCommand();
	void Activate(bool on);
};

#endif
