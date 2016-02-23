#ifndef CATAPULT_H
#define CATAPULT_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"

//The subsystem for the shooting mechanism for the robot

class Catapult: public Subsystem
{
	static constexpr double SHOOTER_MAXCURRENT = 15.0;
private:
	static Catapult* m_pInstance;
	bool m_bOnPID;
	CANTalon* m_shooterController;
	bool m_bResetStepOneDone;
	Timer m_currentTimer;
	Timer m_voltageTimer;

	Catapult();
	Catapult(Catapult const&);
	Catapult& operator=(Catapult const&);
public:
	const int TOP_ZONE = 34;
	const int SLOW_ZONE = 3;

	static Catapult* GetInstance();
	void InitDefaultCommand();
	void toSetpoint(float goal);
	void moveCatapult(float goal);
	void readyShot(int goal);
	bool isBottomHit() { return !m_shooterController->GetReverseLimitOK(); };
	double GetPosition() { return m_shooterController->GetPosition(); };
	double GetSpeed() { return m_shooterController->GetSpeed(); };
	double GetPIDError() { return (double)(m_shooterController->GetClosedLoopError())/RATIO_WINCHMOTORENCODERTICKSTOINCH; };
	bool CheckZero();
//	bool WatchCurrent();
};

#endif
