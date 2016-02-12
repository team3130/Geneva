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
		video->SetLocationQueueSize(10.0 * SmartDashboard::GetNumber("DB/Slider 0",0));
		if(!video->m_display) {
			frcReadImage(image,RobotVideo::IMG_FILE_NAME);
			CameraServer::GetInstance()->SetImage(image);
			//frcDispose(image);
			video->m_display = true;
		}

		video->mutex_lock();
		if (video->HaveHeading() > 0) {
			SmartDashboard::PutNumber("Video Heading", video->GetTurn());
			SmartDashboard::PutNumber("Video Distance", video->GetDistance());
		}
		video->mutex_unlock();
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
