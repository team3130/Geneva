#include "CameraAim.h"
#include "Subsystems/Chassis.h"
#include "OI.h"
#include "Misc/Video.h"

CameraAim::CameraAim(Target_side side)
	: m_side(side)
	, m_prevAngle(0)
{
	Requires(Chassis::GetInstance());
}

// Called just before this Command runs the first time
void CameraAim::Initialize()
{
	timer.Reset();
	timer.Start();
	m_prevAngle = nan("NaN");
}

// Called repeatedly when this Command is scheduled to run
void CameraAim::Execute()
{
	Chassis *chassis = Chassis::GetInstance();
	OI* oi = OI::GetInstance();
	if (chassis == nullptr or oi == nullptr) return;

	double angularVelocity = chassis->GetAngle() - m_prevAngle;

	if (m_prevAngle == nan("NaN") or timer.Get() > AIM_COOLDOWN) {
		float turn0 = 0;
		float turn1 = 0;
		float turn = 0;
		size_t nTurns = 0;
		RobotVideo::GetInstance()->mutex_lock();
		nTurns = RobotVideo::GetInstance()->HaveHeading();
		if(nTurns > 0) turn0 = RobotVideo::GetInstance()->GetTurn(0);
		if(nTurns > 1) turn1 = RobotVideo::GetInstance()->GetTurn(1);
		RobotVideo::GetInstance()->mutex_unlock();
		std::ostringstream oss7;
		oss7 << " T:" << nTurns << " 0:" << turn0 << " 1:" << turn1;
		SmartDashboard::PutString("DB/String 7", oss7.str());

		if (nTurns > 0) {
			if (nTurns > 1) {
				switch (m_side) {
				case kRight:
					turn = turn0 > turn1 ? turn1 : turn0;
					break;
				case kLeft:
					turn = turn0 > turn1 ? turn0 : turn1;
					break;
				default:
					turn = turn0;
				}
			}
			else turn = turn0;

			chassis->HoldAngle(turn);
			timer.Reset();
		}
	}
	else if (fabs(angularVelocity) > MAX_ANGULAR_V) {
		timer.Reset();
	}

	std::ostringstream oss6;
	oss6 << "S:"<< m_side << " Vel: " << (int)(1000.0*angularVelocity)/1000.0 << " T: " << 1000.0*timer.Get();
	SmartDashboard::PutString("DB/String 6", oss6.str());

	// Y-axis positive is down. We want positive - up. Flip it!
	double LSpeed = -oi->stickL->GetY();
	double RSpeed = -oi->stickR->GetY();
	double LMultiplier = (0.5 * oi->stickL->GetZ()) + 0.5;
	double RMultiplier = (0.5 * oi->stickR->GetZ()) + 0.5;
	double moveSpeed = m_side == kLeft
			? LSpeed * LMultiplier
			: RSpeed * RMultiplier;
	moveSpeed *= fabs(moveSpeed); // Square it here so the drivers will feel like it's squared
	chassis->DriveStraight(moveSpeed);

	m_prevAngle = chassis->GetAngle();
}

// Make this return true when this Command no longer needs to run execute()
bool CameraAim::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CameraAim::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CameraAim::Interrupted()
{

}
