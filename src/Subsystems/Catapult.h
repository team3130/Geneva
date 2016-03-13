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
	AnalogInput* m_ballChecker;

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
	double GetPIDError();
	bool CheckZero();
	bool WatchCurrent();
	int BallPresentValue() {return m_ballChecker->GetValue();};
	bool IsBallPresent() {return m_ballChecker->GetValue() > Preferences::GetInstance()->GetInt("Ball Present Value",2048);};	//TODO: Tune Ball Present Value, possibly change comparison direction
};

#endif
