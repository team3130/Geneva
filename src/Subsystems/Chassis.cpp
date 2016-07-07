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

	try{
		//Connect to navX Gyro on MXP port.
		m_navX = new AHRS(SPI::Port::kMXP);
		m_bNavXPresent = true;
	} catch (std::exception ex){
		//If connection fails log the error and fall back to encoder based angle handling.
		std::string str_error = "Error instantiating navX from MXP: ";
		str_error += ex.what();
		DriverStation::ReportError(str_error.c_str());
		m_bNavXPresent = false;
	}


	LiveWindow::GetInstance()->AddActuator("Chassis", "Left Front TalonSRX", m_leftMotorFront);
	LiveWindow::GetInstance()->AddActuator("Chassis", "Left Rear TalonSRX", m_leftMotorRear);
	LiveWindow::GetInstance()->AddActuator("Chassis", "Right Front TalonSRX", m_rightMotorFront);
	LiveWindow::GetInstance()->AddActuator("Chassis", "Right Rear TalonSRX", m_rightMotorRear);

	LiveWindow::GetInstance()->AddSensor("Chassis", "NavX", m_navX);


	m_onPID = false;
	m_onGyro = false;
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

double Chassis::GetAngle(bool forceGyro)
{
	if((m_onGyro || forceGyro) && m_bNavXPresent)
	//if(m_bNavXPresent)									//Always gyro unless not present
	{
		//Angle use wants a faster, more accurate, but drifting angle, for quick use.
		return -m_navX->GetAngle();
	}
	else {
		//Means that angle use wants a driftless angle measure that lasts.
		return ( GetDistanceR() - GetDistanceL() ) * 180 / (Preferences::GetInstance()->GetDouble("ChassisWidth",28.55) * M_PI);
		/*
		 *  Angle is 180 degrees times encoder difference over Pi * the distance between the wheels
		 *	Made from geometry and relation between angle fraction and arc fraction with semicircles.
		 */
	}
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
	m_onGyro=false;		//Gyro needs to be explicitly enabled for each PID turn
	prevAbsBias=0;
}

void Chassis::ResetEncoders()
{
	m_leftMotorFront->SetPosition(0);
	m_rightMotorFront->SetPosition(0);
}

void Chassis::HoldAngle(double angle, bool gyro)
{
	if(!m_onPID) m_onGyro = gyro;		//Prevent changing angle mode when already in a turn
	SetPIDValues();
	GetPIDController()->SetSetpoint(GetAngle() + angle);
	GetPIDController()->Enable();
	m_onPID = true;
}

void Chassis::SetPIDValues()
{
	if(m_bShiftedLow){
		GetPIDController()->SetPID(
				Preferences::GetInstance()->GetDouble("ChassisHighP",0.075),
				Preferences::GetInstance()->GetDouble("ChassisHighI",0.01),
				Preferences::GetInstance()->GetDouble("ChassisHighD",0.09)
		);
	}else{
		GetPIDController()->SetPID(
				Preferences::GetInstance()->GetDouble("ChassisLowP", 0.085),
				Preferences::GetInstance()->GetDouble("ChassisLowI", 0.02),
				Preferences::GetInstance()->GetDouble("ChassisLowD", 0.125)
		);
	}
}
