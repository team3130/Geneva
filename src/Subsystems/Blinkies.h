#ifndef Blinkies_H
#define Blinkies_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Blinkies: public Subsystem
{
private:
	static Blinkies* m_pInstance;
	Blinkies();
	Blinkies(Blinkies const&);
	Blinkies& operator=(Blinkies const&);

	SerialPort* arduino;
public:
	static Blinkies* GetInstance();
	static void PutCommand(std::string command, int param=0);
	void InitDefaultCommand();
};

#endif
