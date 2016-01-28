#include "Shooter.h"
#include "../RobotMap.h"
#include "Subsystems/Shooter.h"
#include "Commands/ControlShooter.h"

ShooterSubsystem* ShooterSubsystem::m_pInstance = NULL;

ShooterSubsystem* ShooterSubsystem::GetInstance()
{
	if(!m_pInstance) m_pInstance = new ShooterSubsystem;
	return m_pInstance;
}

ShooterSubsystem::ShooterSubsystem()
		:Subsystem("Shooter")
		,m_bOnPID(false)
{
	m_bResetStepOneDone = false;
	/*These values are placeholders for last year.
	 *Will be changed based on what is needed
	 */

	m_shooterController = new CANTalon(CAN_SHOOTERMOTOR);
	m_shooterController->ConfigLimitMode(CANTalon::kLimitMode_SwitchInputsOnly);
	m_shooterController->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	m_shooterController->SetFeedbackDevice(CANTalon::QuadEncoder);
	m_shooterController->SetControlMode(CANSpeedController::kPercentVbus);
	m_shooterController->SetPID(0,0,0);

}

void ShooterSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ControlShooterCommand());
}

//Modifies the shooter wheel speed with the value speed


void ShooterSubsystem::toSetpoint(int goal)
{
	if(!m_bOnPID){
		m_bOnPID = true;
		double termP = 1;//TODO: be turned into Preferences::GetInstance
		double termI = 0;//TODO: be turned into Preferences::GetInstance
		double termD = 0;//TODO: be turned into Preferences::GetInstance
		//Add ramp rate later if necessary
		m_shooterController->SetControlMode(CANSpeedController::kPosition);
		m_shooterController->SetPID(termP,termI,termD);
		m_shooterController->EnableControl();
	}
	m_shooterController->Set(goal);
}

void ShooterSubsystem::moveShooter(float speed) {
	m_bOnPID = false;
	m_shooterController->SetControlMode(CANSpeedController::kPercentVbus);
	//TODO add ramp rates
	if (speed >= 0) {
		if (GetPosition() < TOP_ZONE) {
			m_shooterController->Set(speed);
		}
		else {
			m_shooterController->Set(0);
		}
	} else if (!CheckZero()) {
		if (GetPosition() < SLOW_ZONE) {
			m_shooterController->Set(0.5 * speed);
		} else {
			m_shooterController->Set(speed);
		}
	}
	else {
		m_shooterController->Set(0);
	}
}

bool ShooterSubsystem::CheckZero(){
	if(isBottomHit()){
		m_shooterController->SetPosition(0);
		return true;
	}
	else return false;
}

void ShooterSubsystem::readyShot(int goal)
{
	if(!CheckZero() && m_bResetStepOneDone){
		moveShooter(-.8);
	}else{
		m_bResetStepOneDone = true;
		CheckZero();
	}

	if(m_bResetStepOneDone){
		toSetpoint(goal);
		m_bResetStepOneDone = false;
	}
}
