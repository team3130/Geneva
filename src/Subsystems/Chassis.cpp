#include "Subsystems/Chassis.h"
#include "Commands/DefaultDrive.h"

Chassis* Chassis::m_pInstance = NULL;

Chassis* Chassis::GetInstance()
{
	if(!m_pInstance) m_pInstance = new Chassis;
	return m_pInstance;
}

Chassis::Chassis() : PIDSubsystem("Chassis", 0.05, 0.01, 0.15)
{
	m_leftMotorFront = new CANTalon(CAN_LEFTMOTORFRONT);
	m_leftMotorRear = new CANTalon(CAN_LEFTMOTORREAR);
	m_rightMotorFront = new CANTalon(CAN_RIGHTMOTORFRONT);
	m_rightMotorRear = new CANTalon(CAN_RIGHTMOTORREAR);
	m_leftMotorFront->ConfigEncoderCodesPerRev(RATIO_DRIVEENCODERTICKSTOINCH);
	m_rightMotorFront->ConfigEncoderCodesPerRev(RATIO_DRIVEENCODERTICKSTOINCH);

	m_drive = new RobotDrive(m_leftMotorFront, m_leftMotorRear, m_rightMotorFront, m_rightMotorRear);
	m_drive->SetSafetyEnabled(false);
	m_shifter = new Solenoid(CAN_PNMMODULE, PNM_GEARSHIFTER);
	m_bShiftedLow = false;

	LiveWindow::GetInstance()->AddActuator("Chassis", "Left Front TalonSRX", m_leftMotorFront);
	LiveWindow::GetInstance()->AddActuator("Chassis", "Left Rear TalonSRX", m_leftMotorRear);
	LiveWindow::GetInstance()->AddActuator("Chassis", "Right Front TalonSRX", m_rightMotorFront);
	LiveWindow::GetInstance()->AddActuator("Chassis", "Right Rear TalonSRX", m_rightMotorRear);

	m_onPID = false;
	moveSpeed = 0;
}

void Chassis::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new DefaultDrive());
}

//Arcade Drives with the values of move as the forward value, and turn as the turning value
void Chassis::Drive(double moveL, double moveR, bool quad)
{
	m_drive->TankDrive(moveL, moveR, quad);
}

void Chassis::Shift(bool shiftDown)
{
	m_shifter->Set(shiftDown);
	m_bShiftedLow = shiftDown;
}

double Chassis::GetAngle()
{
	return ( m_leftMotorFront->GetEncPosition() - m_rightMotorFront->GetEncPosition() ) * 180 / (25.5 * M_PI);
	/*
	 *  Angle is 180 degrees times encoder difference over Pi * the distance between the wheels
	 *	Made from geometry and relation between angle fraction and arc fraction with semicircles.
	 *  Negative because our encoders connected backwards
	 */
}

double Chassis::ReturnPIDInput()
{
	return GetAngle();
}

void Chassis::UsePIDOutput(double bias)
{
	const double speedLimit = 0.65;
	SmartDashboard::PutNumber("Turn PID bias",bias);
	if(bias >  speedLimit) bias = speedLimit;
	if(bias < -speedLimit) bias = -speedLimit;
	double speed_L = moveSpeed-bias;
	double speed_R = moveSpeed+bias;
	m_drive->TankDrive(speed_L, speed_R, false);
}

double Chassis::GetDistance()
{
	return ( m_leftMotorFront->GetEncPosition() + m_rightMotorFront->GetEncPosition() ) / 2.0;
}

void Chassis::ResetEncoders()
{
	m_leftMotorFront->SetPosition(0);
	m_rightMotorFront->SetPosition(0);
}

void Chassis::HoldAngle(double angle)
{
	GetPIDController()->SetSetpoint(GetAngle() + angle);
	GetPIDController()->Enable();
	m_onPID = true;
}
