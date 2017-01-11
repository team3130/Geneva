#ifndef CATAPULT_H
#define CATAPULT_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"
#include "CANTalon.h"

//The subsystem for the shooting mechanism for the robot

class Catapult: public Subsystem
{
	static constexpr double SHOOTER_MAXCURRENT = 40.0;
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
	static constexpr double TOP_ZONE = 26;
	static constexpr double SLOW_ZONE = 3;

	static Catapult* GetInstance();
	void InitDefaultCommand();
	void toSetpoint(float goal);
	void moveCatapult(float goal);
	void readyShot(int goal);
	bool isBottomHit() { return m_shooterController->IsRevLimitSwitchClosed(); };
	double GetPosition();
	double GetSpeed() { return m_shooterController->GetSpeed(); };
	int GetPIDError();
	bool OnTarget();
	bool CheckZero();
	bool WatchCurrent();
};

#endif
