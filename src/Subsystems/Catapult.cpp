#include "../RobotMap.h"
#include "Commands/ControlCatapult.h"
#include "Subsystems/Catapult.h"

Catapult* Catapult::m_pInstance = NULL;

Catapult* Catapult::GetInstance()
{
	if(!m_pInstance) m_pInstance = new Catapult;
	return m_pInstance;
}

Catapult::Catapult()
		:Subsystem("Catapult")
		,m_bOnPID(false)
		,m_limitSwitch(DIO_CATAPULTBOTTOMLIMIT)
		,m_currentTimer()
{
	m_bResetStepOneDone = false;
	m_shooterController = new CANTalon(CAN_SHOOTERMOTOR);
	m_shooterController->ConfigLimitMode(CANTalon::kLimitMode_SwitchInputsOnly);
	m_shooterController->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	m_shooterController->SetFeedbackDevice(CANTalon::QuadEncoder);
	m_shooterController->SetControlMode(CANSpeedController::kPercentVbus);
	m_shooterController->SetPID(0,0,0);

	m_shooterController->ConfigEncoderCodesPerRev(RATIO_WINCHMOTORENCODERTICKSTOINCH);

	LiveWindow::GetInstance()->AddActuator("Catapult","Winch Talon",m_shooterController);

	m_currentTimer.Reset();
	m_currentTimer.Start();
}

void Catapult::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ControlCatapult());
}

//Modifies the shooter wheel speed with the value speed


void Catapult::toSetpoint(float goal)
{
	if(!m_bOnPID){
		m_bOnPID = true;
		double termP = Preferences::GetInstance()->GetDouble("Catapult P Value", 1);
		double termI = Preferences::GetInstance()->GetDouble("Catapult I Value", 0);
		double termD = Preferences::GetInstance()->GetDouble("Capapult D Value", 0);
		//Add ramp rate later if necessary
		m_shooterController->SetControlMode(CANSpeedController::kPosition);
		m_shooterController->SetPID(termP,termI,termD);
		m_shooterController->EnableControl();
	}
	m_shooterController->Set(goal);
}

void Catapult::moveCatapult(float speed) {
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

bool Catapult::CheckZero(){
	if(isBottomHit() or WatchCurrent()){
		m_shooterController->SetPosition(0);
		return true;
	}
	else return false;
}

bool Catapult::WatchCurrent() {
	if (m_shooterController->GetOutputCurrent() > SHOOTER_MAXCURRENT) {
		if (m_currentTimer.Get() > SHOOTER_MAXTIME) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		m_currentTimer.Reset();
		return false;
	}
}
