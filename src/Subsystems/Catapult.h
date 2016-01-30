#ifndef CATAPULT_H
#define CATAPULT_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"

//The subsystem for the shooting mechanism for the robot

class Catapult: public Subsystem
{
private:
	const int SLOW_ZONE = 300; //TODO Move these numbers somewhere out
	const int TOP_ZONE = 4200; //     They are encoder model dependent
	static Catapult* m_pInstance;
	bool m_bOnPID;
	CANTalon* m_shooterController;
	bool m_bResetStepOneDone;

	Catapult();
	Catapult(Catapult const&);
	Catapult& operator=(Catapult const&);
public:
	static Catapult* GetInstance();
	void InitDefaultCommand();
	void toSetpoint(int goal);
	void moveCatapult(float goal);
	void readyShot(int goal);
	bool isBottomHit() { return !m_shooterController->IsRevLimitSwitchClosed(); };
	double GetPosition() { return m_shooterController->GetPosition(); };
	double GetSpeed() { return m_shooterController->GetSpeed(); };
	int GetPIDError() { return m_shooterController->GetClosedLoopError(); };
	bool CheckZero();

};

#endif
