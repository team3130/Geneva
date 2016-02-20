#include "CameraAim.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/Catapult.h"
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
	RobotVideo::GetInstance()->SetHeadingQueueSize(0);
	RobotVideo::GetInstance()->SetLocationQueueSize(10);
}

// Called repeatedly when this Command is scheduled to run
void CameraAim::Execute()
{
	Chassis *chassis = Chassis::GetInstance();
	OI* oi = OI::GetInstance();
	if (chassis == nullptr or oi == nullptr) return;

	double angularVelocity = chassis->GetAngle() - m_prevAngle;

	if (m_prevAngle == nan("NaN") or timer.Get() > AIM_COOLDOWN) {
		float turn = 0;
		float dist = 0;
		size_t nTurns = 0;

		RobotVideo::GetInstance()->mutex_lock();
		nTurns = RobotVideo::GetInstance()->HaveHeading();
		if(nTurns > 0) {
			turn = RobotVideo::GetInstance()->GetTurn(0);
			dist = RobotVideo::GetInstance()->GetDistance(0);
		}
		if(m_side == kRight and nTurns > 1) {
			turn = RobotVideo::GetInstance()->GetTurn(1);
			dist = RobotVideo::GetInstance()->GetDistance(1);
		}
		RobotVideo::GetInstance()->mutex_unlock();

		if (nTurns > 0) {
			if (dist > 100) {
				// Magic function.
				//double m_catStop =2*log(7.75*dist-770)+7.5;
				//Catapult::GetInstance()->toSetpoint(m_catStop);

				// The height of the goal is 96 inches. We want the distance to the tower base.
				dist = sqrt(dist*dist - 96*96);
				// Now as we know the actual distance, the camera offset over that distance is the adjustment angle's tangent
				turn += atan2f(RobotVideo::CAMERA_OFFSET, dist);
			}
			chassis->HoldAngle(turn);
			timer.Reset();
		}
	}
	else if (fabs(angularVelocity) > MAX_ANGULAR_V) {
		timer.Reset();
	}
	m_prevAngle = chassis->GetAngle();

	double LSpeed = oi->stickL->GetY();
	double RSpeed = oi->stickR->GetY();
	double moveSpeed = fabs(LSpeed) > fabs(RSpeed) ? LSpeed : RSpeed;
	moveSpeed *= fabs(moveSpeed); // Square it here so the drivers will feel like it's squared
	chassis->DriveStraight(moveSpeed);
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
