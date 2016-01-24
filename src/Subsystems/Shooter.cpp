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
	/*These values are placeholders for last year.
	 *Will be changed based on what is needed
	 */

	m_shooterController = new CANTalon(PORT_SHOOTERMOTOR);
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
		double termP = 0;//TODO: be turned into Prefernces::GetInstance
		double termI = 0;//TODO: be turned into Prefernces::GetInstance
		double termD = 0;//TODO: be turned into Prefernces::GetInstance
		//Add ramp rate later if nessecary
		m_shooterController->SetControlMode(CANSpeedController::kPosition);
		m_shooterController->SetPID(termP,termI,termD);
		m_shooterController->EnableControl();
	}
	m_shooterController->Set(goal);



}

void ShooterSubsystem::moveShooter(float goal)
{
m_bOnPID = false;
						//TODO add ramp rates
if(goal > 0 and getLimitSwitchTop()){
m_shooterController->SetControlMode(CANSpeedController::kPercentVbus);
if(GetPosition () > 3000){ //TODO Get actual value for this
	m_shooterController->Set(0.5*goal);
}else{
	m_shooterController->Set(goal);

}
}else if(goal < 0 and getLimitSwitchBot()){
	m_shooterController->SetControlMode(CANSpeedController::kPercentVbus);
	if(GetPosition()<600){	//TODO Get actual value for this
		m_shooterController->Set(0.5*goal);
	}else{
		m_shooterController->Set(goal);
	}
}else if(m_shooterController->GetControlMode() == CANSpeedController::kPercentVbus){
	toSetpoint(GetPosition());
}
	CheckZero();
}

bool ShooterSubsystem::CheckZero(){
	if(!getLimitSwitchBot()){
		m_shooterController->SetPosition(0);
		//TODO Some type of robot sensors to reset lifter
		return true;

	}
	else return false;
}

