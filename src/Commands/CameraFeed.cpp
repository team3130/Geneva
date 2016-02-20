#include "CameraFeed.h"
#include "Misc/Video.h"
#include "Vision/VisionAPI.h"

CameraFeed::CameraFeed()
	: image(frcCreateImage(IMAQ_IMAGE_RGB))
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void CameraFeed::Initialize()
{
	if (RobotVideo* video = RobotVideo::GetInstance()) {
		video->SetHeadingQueueSize(0);
		video->SetLocationQueueSize(0);
		video->Enable();
	}
}

// Called repeatedly when this Command is scheduled to run
void CameraFeed::Execute()
{
	if (RobotVideo* video = RobotVideo::GetInstance()) {
		if(!video->m_display) {
			frcReadImage(image,RobotVideo::IMG_FILE_NAME);
			CameraServer::GetInstance()->SetImage(image);
			//frcDispose(image);
			video->m_display = true;
		}

		float turn0, turn1, dist0, dist1;
		size_t nGoals;
		video->mutex_lock();
		nGoals = video->HaveHeading();
		if (nGoals > 0) {
			turn0 = video->GetTurn(0);
			dist0 = video->GetDistance(0);
		}
		if (nGoals > 1) {
			turn1 = video->GetTurn(1);
			dist1 = video->GetDistance(1);
		}
		video->mutex_unlock();

		if (nGoals > 0) {
			SmartDashboard::PutNumber("Video Heading L", turn0);
			SmartDashboard::PutNumber("Video Distance L", dist0);
		}
		if (nGoals > 1) {
			SmartDashboard::PutNumber("Video Heading R", turn1);
			SmartDashboard::PutNumber("Video Distance R", dist1);
		}
		else {
			SmartDashboard::PutNumber("Video Heading R", turn0);
			SmartDashboard::PutNumber("Video Distance R", dist0);
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
	if (RobotVideo* video = RobotVideo::GetInstance()) {
		video->Disable();
	}
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CameraFeed::Interrupted()
{
	End();
}
