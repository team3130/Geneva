#include "Subsystems/Chassis.h"
#include "Commands/DefaultDrive.h"
#include "Misc/Video.h"

#define CHASSIS_USE_ENCODERS

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
	m_leftMotorFront->SetSensorDirection(false);
	m_rightMotorFront->SetSensorDirection(true);
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

void Chassis::DriveArcade(double move, double turn, bool squaredInputs)
{

	m_drive->ArcadeDrive(move, turn, squaredInputs);
}

void Chassis::Shift(bool shiftDown)
{
	m_shifter->Set(shiftDown);
	m_bShiftedLow = shiftDown;
}

double Chassis::GetAngle()
{
	return ( m_rightMotorFront->GetPosition() - m_leftMotorFront->GetPosition() ) * 180 / (25.5 * M_PI);
	/*
	 *  Angle is 180 degrees times encoder difference over Pi * the distance between the wheels
	 *	Made from geometry and relation between angle fraction and arc fraction with semicircles.
	 *  Negative because our encoders connected backwards
	 */
}

double Chassis::ReturnPIDInput()
{
#ifdef CHASSIS_USE_ENCODERS
	return GetAngle();
#else
	RobotVideo::GetInstance()->mutex_lock();
	size_t nTurns = RobotVideo::GetInstance()->HaveHeading();
	float turn, dist;
	if(nTurns > 0) {
		turn = RobotVideo::GetInstance()->GetTurn(0);
		dist = RobotVideo::GetInstance()->GetDistance(0);
	}
	if(false /*m_side == kRight*/ and nTurns > 1) {
		turn = RobotVideo::GetInstance()->GetTurn(1);
		dist = RobotVideo::GetInstance()->GetDistance(1);
	}
	RobotVideo::GetInstance()->mutex_unlock();

	if (nTurns > 0) {
		if (dist > 0) {
			// The camera offset over the distance is the adjustment angle's tangent
			turn += atan2f(Preferences::GetInstance()->GetFloat("CameraOffset",RobotVideo::CAMERA_OFFSET), dist);
		}
		m_lastAngle = -turn;
	}
	return m_lastAngle;
#endif
}

void Chassis::UsePIDOutput(double bias)
{
	const double speedLimit = 1.0;
	if(bias >  speedLimit) bias = speedLimit;
	if(bias < -speedLimit) bias = -speedLimit;
	double speed_L = moveSpeed-bias;
	double speed_R = moveSpeed+bias;
	m_drive->TankDrive(speed_L, speed_R, false);
}

double Chassis::GetDistance()
{
	return ( GetDistanceL() + GetDistanceR() ) / 2.0;
}

void Chassis::ResetEncoders()
{
	m_leftMotorFront->SetPosition(0);
	m_rightMotorFront->SetPosition(0);
}

void Chassis::HoldAngle(double angle)
{
	GetPIDController()->SetPID(
			Preferences::GetInstance()->GetDouble("ChassisP", 0.05),
			Preferences::GetInstance()->GetDouble("ChassisI", 0.01),
			Preferences::GetInstance()->GetDouble("ChassisD", 0.15));
#ifdef CHASSIS_USE_ENCODERS
	GetPIDController()->SetSetpoint(GetAngle() + angle);
	GetPIDController()->SetToleranceBuffer(5); // Num cycles to average onTarget over
#else
	GetPIDController()->SetSetpoint(0);
#endif
	GetPIDController()->Enable();
	m_onPID = true;
}
