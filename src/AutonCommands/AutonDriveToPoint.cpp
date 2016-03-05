#include "AutonDriveToPoint.h"
#include "Subsystems/Chassis.h"

AutonDriveToPoint::AutonDriveToPoint()
	:PIDCommand(1,0,0) //TODO: Tune PID Values
	,m_speed(0)
	,m_setPoint(0)
	,m_angle(0)
	,m_threshold(0)
	,m_timeout(0)
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
	if(output > m_speed) output = m_speed;
	if(output < -m_speed) output = -m_speed;
	Chassis::GetInstance()->Drive(output,0);
}

void AutonDriveToPoint::SetParam(double travelDistance, double angle, double speed, double tolerance, double timeout)
{
	m_setPoint = travelDistance;
	m_speed = speed;
	m_angle = angle;
	m_threshold = tolerance;
	m_timeout = timeout;
	GetPIDController()->SetSetpoint(m_setPoint);
	GetPIDController()->SetAbsoluteTolerance(m_threshold);
}


// Called just before this Command runs the first time
void AutonDriveToPoint::Initialize()
{
	Chassis::GetInstance()->ResetEncoders();
	GetPIDController()->Disable();
	GetPIDController()->SetSetpoint(m_setPoint);
	GetPIDController()->SetAbsoluteTolerance(m_threshold);

	Chassis::GetInstance()->HoldAngle(m_angle);
	GetPIDController()->Reset();
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
	if(GetPIDController()->OnTarget()) return true;
	return (m_timeout > 0 && timer->Get() > m_timeout);
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

}
