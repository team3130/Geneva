#include "CameraAim.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/Catapult.h"
#include "OI.h"
#include "Misc/Video.h"

CameraAim::CameraAim(Target_side side, bool auton)
	: m_side(side)
	, m_prevAngle(0)
	, m_target(0)
	, m_gotLock(false)
	, m_gotVisual(false)
	, m_auton(auton)
{
	Requires(Chassis::GetInstance());
}

// Called just before this Command runs the first time
void CameraAim::Initialize()
{
	frame_timer.Reset();
	frame_timer.Start();
	m_prevAngle = Chassis::GetInstance()->GetAngle();
	cycle_timer.Reset();
	cycle_timer.Start();
	RobotVideo::GetInstance()->SetHeadingQueueSize(0);
	RobotVideo::GetInstance()->SetLocationQueueSize(10);
	Chassis::GetInstance()->Shift(true);
	m_gotVisual = false;
	m_gotLock = false;
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
	// Top slider sets the bias from "New" (0) to "Old" (5) balls
	double bias = SmartDashboard::GetNumber("DB/Slider 0", 0) / 5;

	if (dist > 192) return 18.4;

	// Interpolated by Google Spreadsheets
	double a = -2.573e-4 -6e-7 * bias;
	double b = 0.088 -2e-3 * bias;
	double c = 10.696 +0.042 * bias;

	return a * dist * dist + b * dist + c;
}

// Called repeatedly when this Command is scheduled to run
void CameraAim::Execute()
{
	Chassis *chassis = Chassis::GetInstance();
	OI* oi = OI::GetInstance();
	if (chassis == nullptr or oi == nullptr) return;

	if (!m_gotVisual or frame_timer.Get() > Preferences::GetInstance()->GetDouble("CameraLag", AIM_COOLDOWN)) {
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
				turn += (180.0/M_PI) * atan2f(Preferences::GetInstance()->GetFloat("CameraOffset",RobotVideo::CAMERA_OFFSET), dist);
				m_gotLock = fabs(turn) < (180.0/M_PI) * atan2f(Preferences::GetInstance()->GetDouble("CameraTolerance", 4.0), dist);
			}
			chassis->HoldAngle(turn);
			frame_timer.Reset();
			m_target = turn;
			m_gotVisual = true;
		}
		else {
			m_gotVisual = false;
		}
	}
	else if (cycle_timer.Get() > 0) {
		double angular_v = (chassis->GetAngle() - m_prevAngle) / cycle_timer.Get();
		if (fabs(angular_v) > Preferences::GetInstance()->GetDouble("AngularVelocity", MAX_ANGULAR_V))
			frame_timer.Reset();

		// Take this measurement for tuning purposes. Remove after the tuning is done
		SmartDashboard::PutNumber("Angular Velocity", angular_v);
	}

	m_prevAngle = chassis->GetAngle();
	cycle_timer.Reset();

	// Check the catapult output current for safety
	if (Catapult::GetInstance()->WatchCurrent()) Catapult::GetInstance()->moveCatapult(0);

	// Drive forward or back while aiming
	double moveSpeed = -oi->stickL->GetY();
	if (m_gotVisual) {
		moveSpeed *= fabs(moveSpeed); // Square it here so the drivers will feel like it's squared
		chassis->DriveStraight(moveSpeed);
	}
	else {
		// If we still have no visual the chassis is not in PID mode yet, so drive Arcade
		chassis->DriveArcade(moveSpeed, 0, true);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CameraAim::IsFinished()
{
	if (m_gotVisual and m_gotLock) {
		SmartDashboard::PutBoolean("Target locked", true);
		SmartDashboard::PutBoolean("DB/LED 0", true);
		if (m_auton) return true;
	}
	else {
		SmartDashboard::PutBoolean("Target locked", false);
		SmartDashboard::PutBoolean("DB/LED 0", false);
	}
	return false;
}

// Called once after isFinished returns true
void CameraAim::End()
{
	SmartDashboard::PutBoolean("Target locked", false);
	SmartDashboard::PutBoolean("DB/LED 0", false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CameraAim::Interrupted()
{
	End();
}
