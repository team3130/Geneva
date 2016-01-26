#ifndef SHOOTER_H
#define SHOOTER_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"

//The subsystem for the shooting mechanism for the robot

class ShooterSubsystem: public Subsystem
{
private:
	static ShooterSubsystem* m_pInstance;
	bool m_bOnPID;
	CANTalon* m_shooterController;
	bool m_bResetStepOneDone;

	ShooterSubsystem();
	ShooterSubsystem(ShooterSubsystem const&);
	ShooterSubsystem& operator=(ShooterSubsystem const&);
public:
	static ShooterSubsystem* GetInstance();
	void InitDefaultCommand();
	void toSetpoint(int goal);
	void moveShooter(float goal);
	void readyShot(int goal);
	bool getLimitSwitchTop(){ return m_shooterController->IsFwdLimitSwitchClosed();}
	bool getLimitSwitchBot(){ return m_shooterController->IsRevLimitSwitchClosed(); }
	double GetPosition() { return m_shooterController->GetPosition(); };
	double GetSpeed() { return m_shooterController->GetSpeed(); };
	bool CheckZero();

};

#endif
