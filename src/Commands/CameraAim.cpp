#include "CameraAim.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/Catapult.h"
#include "OI.h"
#include "Misc/Video.h"
#include "Subsystems/Blinkies.h"
#include "Subsystems/CatStopCalculations.h"

CameraAim::CameraAim(Target_side side, bool auton)
	: m_side(side)
	, m_prevAngle(0)
	, m_target(0)
	, m_gotLock(false)
	, m_gotVisual(false)
	, m_auton(auton)
{
	Requires(Chassis::GetInstance());
	Requires(Catapult::GetInstance());
}

// Called just before this Command runs the first time
void CameraAim::Initialize()
{
	m_locationQueue = std::queue<LocationRecord>();
	m_prevAngle = Chassis::GetInstance()->GetAngle();
	RobotVideo::GetInstance()->SetHeadingQueueSize(0);
	RobotVideo::GetInstance()->SetLocationQueueSize(0);
	Chassis::GetInstance()->Shift(true);
	Chassis::GetInstance()->HoldAngle(0, false);
	m_gotVisual = false;
	m_gotLock = false;
	location_timer.Reset();
	location_timer.Start();
	frame_timer.Reset();
	frame_timer.Start();
	cycle_timer.Reset();
	cycle_timer.Start();
}

void CameraAim::SetParam(Target_side kSide)
{
	m_side = kSide;
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
	// Interpolated by Google Spreadsheets: boulder's horizontal velocity at certain distance
	double velocity = -5.955e-3 * dist * dist +2.141 * dist +77.056;
	double phase = dist / velocity;

	// Phase is the time a boulder takes to get to the target. Adjust distance accordingly
	dist -= speed * phase;

	double stop = CatStopCalculations::GetInstance()->GetStop(dist);

	return stop - Preferences::GetInstance()->GetDouble("Vision Hight Offset", 0);
}

// Called repeatedly when this Command is scheduled to run
void CameraAim::Execute()
{
	Chassis *chassis = Chassis::GetInstance();
	OI* oi = OI::GetInstance();
	if (chassis == nullptr or oi == nullptr) return;

	if (!m_gotVisual or frame_timer.Get() > Preferences::GetInstance()->GetDouble("CameraCooldown", AIM_COOLDOWN)) {
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
				// Clear the queue of expired records if any
				double expirationTime = location_timer.Get() - Preferences::GetInstance()->GetDouble("CameraLag", 0.25);
				while (!m_locationQueue.empty() and m_locationQueue.front().time < expirationTime)
					m_locationQueue.pop();

				// Calculate chassis's speed as location change over passed time...
				// if enabled and correct data is available
				double speed = 0;
				if (SmartDashboard::GetBoolean("DB/Button 0",false) and !m_locationQueue.empty()) {
					double dX = chassis->GetDistance() - m_locationQueue.front().dist;
					double dT = location_timer.Get() - m_locationQueue.front().time;
					if (dT > 0) speed = dX / dT;
					// Also adjust distance to target since all this is Camera Lag based
					dist -= dX;
				}

				// Call the Magic function to determine the stop angle.
				float catStop = calculateStop(dist, speed);
				if (catStop > Catapult::TOP_ZONE) catStop = Catapult::TOP_ZONE;
				if (catStop < Catapult::SLOW_ZONE) catStop = Catapult::SLOW_ZONE;
				Catapult::GetInstance()->toSetpoint(catStop);

				// The camera offset over the distance is the adjustment angle's tangent
				turn += (180.0/M_PI) * atan2f(Preferences::GetInstance()->GetFloat("CameraOffset",RobotVideo::CAMERA_OFFSET), dist);
				double camTolerance = (180.0/M_PI) * atan2f(Preferences::GetInstance()->GetDouble("CameraTolerance", 3.5), dist);
				camTolerance -= Preferences::GetInstance()->GetDouble("CameraDeviation", 0.8);
				if (camTolerance < 0.1) camTolerance = 0.1;
				m_gotLock = ((fabs(turn) < camTolerance) && Catapult::GetInstance()->OnTarget());
				int proxima = 0;
				if (!m_gotLock && camTolerance > 0) proxima = abs(turn / camTolerance);
				if (proxima > 9) proxima = 9;
				Blinkies::PutCommand("Aim_", proxima);
			}
			chassis->HoldAngle(turn, true);
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
		if (fabs(angular_v) > Preferences::GetInstance()->GetDouble("AngularVelocity", MAX_ANGULAR_V)
			or fabs(chassis->GetPIDError()) > Preferences::GetInstance()->GetDouble("AimResetAngle", 0.5))
			frame_timer.Reset();

		// Take this measurement for tuning purposes. Remove after the tuning is done
		SmartDashboard::PutNumber("Angular Velocity", angular_v);
	}

	m_prevAngle = chassis->GetAngle();
	cycle_timer.Reset();

	LocationRecord record;
	record.dist = chassis->GetDistance();
	record.time = location_timer.Get();
	m_locationQueue.push(record);

	// Check the catapult output current for safety
	if (Catapult::GetInstance()->WatchCurrent()) Catapult::GetInstance()->moveCatapult(0);

	// Drive forward or back while aiming
	double moveSpeed = -oi->stickL->GetY();
	moveSpeed *= fabs(moveSpeed); // Square it here so the drivers will feel like it's squared
	chassis->DriveStraight(moveSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool CameraAim::IsFinished()
{
	if (m_gotVisual and m_gotLock) {
		SmartDashboard::PutBoolean("Target locked", true);
		SmartDashboard::PutBoolean("DB/LED 0", true);
		if (m_auton and frame_timer.Get() > Preferences::GetInstance()->GetDouble("CameraCooldown", AIM_COOLDOWN)) {
			return true;
		}
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
