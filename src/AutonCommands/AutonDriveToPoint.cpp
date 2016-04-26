#include "AutonDriveToPoint.h"
#include "Subsystems/Chassis.h"

AutonDriveToPoint::AutonDriveToPoint()
	:PIDCommand(0.1,0,0) //TODO: Tune PID Values
	,m_speed(0)
	,m_setPoint(0)
	,m_angle(0)
	,m_threshold(0)
	,m_lowGear(false)
{
	timer = new Timer();

	Requires(Chassis::GetInstance());
}

AutonDriveToPoint::~AutonDriveToPoint()
{
	delete timer;
}

double AutonDriveToPoint::ReturnPIDInput()
{
	return Chassis::GetInstance()->GetDistance();
}

void AutonDriveToPoint::UsePIDOutput(double output)
{
	double speed = m_speed;
	if (timer->Get() < 0.5) speed = m_speed * timer->Get()/0.5;
	if(output > speed) output = speed;
	if(output < -speed) output = -speed;
	Chassis::GetInstance()->DriveStraight(output);
}

void AutonDriveToPoint::SetParam(double travelDistance, double angle, double speed, double tolerance, bool lowGear)
{
	m_setPoint = travelDistance;
	m_speed = speed;
	m_angle = angle;
	m_threshold = tolerance;
	m_lowGear = lowGear;
	//Chassis::GetInstance()->ResetEncoders();
//	GetPIDController()->SetSetpoint(m_setPoint);
//	GetPIDController()->SetAbsoluteTolerance(m_threshold);
}


// Called just before this Command runs the first time
void AutonDriveToPoint::Initialize()
{
	//Chassis::GetInstance()->ResetEncoders();
	GetPIDController()->Reset();
	GetPIDController()->SetPID(
			Preferences::GetInstance()->GetDouble("StraightP",0.05),
			Preferences::GetInstance()->GetDouble("StraightI",0.01),
			Preferences::GetInstance()->GetDouble("StraightD",0.0)
			);
	GetPIDController()->SetSetpoint(Chassis::GetInstance()->GetDistance() + m_setPoint);
	GetPIDController()->SetAbsoluteTolerance(m_threshold);
	Chassis::GetInstance()->Shift(m_lowGear);

	//Chassis::GetInstance()->ReleaseAngle();
	Chassis::GetInstance()->HoldAngle(m_angle);
	GetPIDController()->Enable();
	timer->Reset();
	timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void AutonDriveToPoint::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool AutonDriveToPoint::IsFinished()
{
	return GetPIDController()->OnTarget();
}

// Called once after isFinished returns true
void AutonDriveToPoint::End()
{
	Chassis::GetInstance()->Drive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonDriveToPoint::Interrupted()
{
End();
}
