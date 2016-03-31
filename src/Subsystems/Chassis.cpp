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
	m_leftMotorFront->SetSensorDirection(false);
	m_rightMotorFront->SetSensorDirection(true);
	m_leftMotorFront->ConfigEncoderCodesPerRev(RATIO_DRIVECODESPERREV);
	m_rightMotorFront->ConfigEncoderCodesPerRev(RATIO_DRIVECODESPERREV);

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
	prevAbsBias = 0;
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

double Chassis::GetSpeedL()
{
	return m_leftMotorFront->GetSpeed() * InchesPerRev / 50.0;
}

double Chassis::GetSpeedR()
{
	return m_rightMotorFront->GetSpeed() * InchesPerRev / 50.0;
}

double Chassis::GetSpeed()
{
	return ( GetSpeedL() + GetSpeedR() ) / 2.0;
}

double Chassis::GetDistanceL()
{
	return m_leftMotorFront->GetPosition() * InchesPerRev;
}

double Chassis::GetDistanceR()
{
	return m_rightMotorFront->GetPosition() * InchesPerRev;
}

double Chassis::GetDistance()
{
	return ( GetDistanceL() + GetDistanceR() ) / 2.0;
}

double Chassis::GetAngle()
{
	return 1.065 * ( GetDistanceR() - GetDistanceL() ) * 180 / (26.75 * M_PI);
	/*
	 *  Angle is 180 degrees times encoder difference over Pi * the distance between the wheels
	 *	Made from geometry and relation between angle fraction and arc fraction with semicircles.
	 */
}

double Chassis::ReturnPIDInput()
{
	return GetAngle();
}

void Chassis::UsePIDOutput(double bias)
{
	// Chassis ramp rate is the limit on the voltage change per cycle to prevent skidding.
	const double speedLimit = prevAbsBias + Preferences::GetInstance()->GetDouble("ChassisRampRate", 0.25);
	if(bias >  speedLimit) bias = speedLimit;
	if(bias < -speedLimit) bias = -speedLimit;
	double speed_L = moveSpeed-bias;
	double speed_R = moveSpeed+bias;
	m_drive->TankDrive(speed_L, speed_R, false);
	prevAbsBias = fabs(bias);
}

void Chassis::ReleaseAngle()
{
	GetPIDController()->Disable();
	m_onPID=false;
	prevAbsBias=0;
}

void Chassis::ResetEncoders()
{
	m_leftMotorFront->SetPosition(0);
	m_rightMotorFront->SetPosition(0);
}

void Chassis::HoldAngle(double angle)
{
	GetPIDController()->SetPID(
			Preferences::GetInstance()->GetDouble("ChassisP", 0.085),
			Preferences::GetInstance()->GetDouble("ChassisI", 0.02),
			Preferences::GetInstance()->GetDouble("ChassisD", 0.125));
	GetPIDController()->SetSetpoint(GetAngle() + angle);
	GetPIDController()->Enable();
	m_onPID = true;
}
