#include "CameraFeed.h"
#include "Misc/Video.h"
#include "Vision/VisionAPI.h"
#include "Vision/nivision.h"

using namespace frc;

CameraFeed::CameraFeed()
	: image(imaqCreateImage(IMAQ_IMAGE_RGB, 1))
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void CameraFeed::Initialize()
{
	RobotVideo::GetInstance()->Enable();
}

// Called repeatedly when this Command is scheduled to run
void CameraFeed::Execute()
{
	if (RobotVideo* video = RobotVideo::GetInstance()) {
		if(not video->m_display) {
			//frcReadImage(image,RobotVideo::IMG_FILE_NAME);
			//CameraServer::GetInstance()->SetImage(image);
			//frcDispose(image);
			video->m_display = true;
		}

		float turnL = 0;
		float distL = 0;
		float turnR = 0;
		float distR = 0;
		size_t nTurns = 0;

		RobotVideo::GetInstance()->mutex_lock();
		nTurns = RobotVideo::GetInstance()->HaveHeading();
		if(nTurns > 0) {
			turnL = RobotVideo::GetInstance()->GetTurn(0);
			distL = RobotVideo::GetInstance()->GetDistance(0);
		}
		if(nTurns > 1) {
			turnR = RobotVideo::GetInstance()->GetTurn(1);
			distR = RobotVideo::GetInstance()->GetDistance(1);
		}
		RobotVideo::GetInstance()->mutex_unlock();

		if (nTurns > 0) {
			SmartDashboard::PutBoolean("FeedLeft", true);
			SmartDashboard::PutNumber("FeedDistL", distL);
			SmartDashboard::PutNumber("FeedTurnL", -turnL);
			if (nTurns > 1) {
				SmartDashboard::PutBoolean("FeedRight", true);
				SmartDashboard::PutNumber("FeedDistR", distR);
				SmartDashboard::PutNumber("FeedTurnR", -turnR);
			}
			else {
				SmartDashboard::PutBoolean("FeedRight", false);
				SmartDashboard::PutNumber("FeedDistR", 0);
				SmartDashboard::PutNumber("FeedTurnR", 0);
			}
		}
		else {
			SmartDashboard::PutBoolean("FeedLeft", false);
			SmartDashboard::PutNumber("FeedDistL", 0);
			SmartDashboard::PutNumber("FeedTurnL", 0);
			SmartDashboard::PutBoolean("FeedRight", false);
			SmartDashboard::PutNumber("FeedDistR", 0);
			SmartDashboard::PutNumber("FeedTurnR", 0);
		}

	}
}

// Make this return true when this Command no longer needs to run execute()
bool CameraFeed::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CameraFeed::End()
{
	RobotVideo::GetInstance()->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CameraFeed::Interrupted()
{
	End();
}
