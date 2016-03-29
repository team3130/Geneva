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
		,m_currentTimer()
		,m_voltageTimer()
{
	m_ballChecker = new AnalogInput(ANG_CATAPULTBALLCHECK);

	m_bResetStepOneDone = false;
	m_shooterController = new CANTalon(CAN_SHOOTERMOTOR);
	m_shooterController->ConfigLimitMode(CANTalon::kLimitMode_SwitchInputsOnly);
	m_shooterController->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	m_shooterController->SetFeedbackDevice(CANTalon::QuadEncoder);
	m_shooterController->SetControlMode(CANSpeedController::kPercentVbus);
	m_shooterController->SetAllowableClosedLoopErr(2);

	m_shooterController->ConfigEncoderCodesPerRev(RATIO_WINCHCODESPERREV);

	LiveWindow::GetInstance()->AddActuator("Catapult","Winch Talon",m_shooterController);

	m_currentTimer.Reset();
	m_currentTimer.Start();
	m_voltageTimer.Reset();
	m_voltageTimer.Start();
}

void Catapult::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ControlCatapult());
}

double Catapult::GetPosition()
{
	 // 0.965 is drum diameter.
	return m_shooterController->GetPosition() * M_PI * 0.965;
}

int Catapult::GetPIDError()
{
	return m_shooterController->GetClosedLoopError();
}

bool Catapult::OnTarget()
{
	return abs(GetPIDError()) < Preferences::GetInstance()->GetInt("WinchTolerance", 45);
}

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
	m_shooterController->Set(goal / (M_PI * 0.965));
}

void Catapult::moveCatapult(float speed) {
	m_bOnPID = false;
	m_shooterController->SetControlMode(CANSpeedController::kPercentVbus);
	if (speed > 0) {
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
	if(isBottomHit()){
		m_shooterController->SetPosition(0);
		return true;
	}
	else return false;
}

bool Catapult::WatchCurrent() {
	if (fabs(m_shooterController->GetOutputVoltage()) < 3.0) m_voltageTimer.Reset();
	if (m_shooterController->GetOutputCurrent() > Preferences::GetInstance()->GetFloat("CatapultMaxCurrent", SHOOTER_MAXCURRENT)) {
		if (m_currentTimer.Get() > Preferences::GetInstance()->GetFloat("CatapultCurrentTime", 0.5)) {
			if (m_voltageTimer.Get() > Preferences::GetInstance()->GetFloat("CatapultStartTime", 0.3)) {
				return true;
			}
		}
	}
	else {
		m_currentTimer.Reset();
	}
	return false;
}
