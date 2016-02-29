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

/**
 * \brief Magic function that returns desired stop angle in rope inches
 *
 * The data collected from repeated shooting at the last night of the build
 * season suggest that the stop angle of the catapult is pretty much a linear
 * function. Here we are going to account for the robot's velocity related
 * to the tower.
 */
double calculateStop(double dist, double speed=0)
{
	// Interpolated by Google Spreadsheets
	return -1.99e-4 * dist*dist + 0.08 * dist + 10.752;
}

// Called repeatedly when this Command is scheduled to run
void CameraAim::Execute()
{
	Chassis *chassis = Chassis::GetInstance();
	OI* oi = OI::GetInstance();
	if (chassis == nullptr or oi == nullptr) return;

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
			if (dist > 0) {
				// Call the Magic function to determine the stop angle.
				float catStop = calculateStop(dist);
				if (catStop > Catapult::TOP_ZONE) catStop = Catapult::TOP_ZONE;
				if (catStop < Catapult::SLOW_ZONE) catStop = Catapult::SLOW_ZONE;
				Catapult::GetInstance()->toSetpoint(catStop);

				// The camera offset over the distance is the adjustment angle's tangent
				turn += atan2f(Preferences::GetInstance()->GetFloat("CameraOffset",RobotVideo::CAMERA_OFFSET), dist);
			}
			chassis->HoldAngle(turn);
			timer.Reset();
		}
	}
	else if (fabs(chassis->GetAngle() - m_prevAngle) > MAX_ANGULAR_V) {
		timer.Reset();
	}

	m_prevAngle = chassis->GetAngle();

	double moveSpeed = -oi->stickL->GetY();
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
