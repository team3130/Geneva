#include "Misc/Video.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Vision/nivision.h"


#include <iostream>
#include <algorithm>
#include <WPILib.h>
#include <Timer.h>
#include "Vision/nivision.h"

const char* RobotVideo::IMG_FILE_NAME = "/var/volatile/tmp/alpha.png";

/**
 * \brief Color filter numbers
 *
 * We use a green ring-light and its color has Hue about 70 in OpenCV's range (0-180)
 * We care about anything that falls between 65 and 90 by the hue but the saturation and
 * brightness can be in a quite wide range.
 */
static const	cv::Vec3i BlobLower(65, 100,  65);
static const	cv::Vec3i BlobUpper(90, 255, 255);

/**
 * \brief Stencil is a simplified "contour" that is an "ideal" shape that we're looking for.
 *
 * The stencil consists of 8 points - the 2d corners of the vision target how it would
 * appear in the picture. The origin is in the left-top corner.
 */
static const 	std::vector<cv::Point> stencil = {
		{ 32, 0 },
		{ 26, 76 },
		{ 184, 76 },
		{ 180, 0 },
		{ 203, 0 },
		{ 212, 100 },
		{ 0, 100 },
		{ 9, 0 }
	};

/* Microsoft HD3000 camera, 424x240, inches */
/* %YAML:1.0
calibration_time: "02/04/16 16:27:55"
image_width: 424
image_height: 240
board_width: 9
board_height: 6
square_size: 9.3000000715255737e-001
# flags: +zero_tangent_dist
flags: 8
avg_reprojection_error: 2.5414490641601828e-001

static const cv::Matx33d camera_matrix( //: !!opencv-matrix
		3.5268678648676683e+002, 0., 2.0327612059375753e+002, 0.,
		3.5189453914759548e+002, 1.2064326427596691e+002, 0., 0., 1. );
static const cv::Matx<double, 5, 1> distortion_coefficients( //: !!opencv-matrix
		1.1831895351666220e-001, -9.2348154326823140e-001, 0., 0.,
		1.4944420484345493e+000 );
*/

RobotVideo* RobotVideo::m_pInstance = NULL;
pthread_t   RobotVideo::m_thread;

RobotVideo::RobotVideo()
	: m_mutex(PTHREAD_MUTEX_INITIALIZER)
	, m_connected(false)
	, m_idle(true)
	, m_boxes()
	, m_turns(MAX_TARGETS)
	, m_display(false)
{

}

void RobotVideo::InitVariables()
{
	// First do some preliminary calculations.

	m_focal_length = Preferences::GetInstance()->GetFloat("CameraFocal", CAPTURE_FOCAL);
	m_zenith = m_focal_length * Preferences::GetInstance()->GetFloat("CameraZeroDist", CAMERA_ZERO_DIST) / Preferences::GetInstance()->GetFloat("CameraHeight", CAMERA_HEIGHT);
	m_horizon = m_focal_length * Preferences::GetInstance()->GetFloat("CameraHeight", CAMERA_HEIGHT) / Preferences::GetInstance()->GetFloat("CameraZeroDist", CAMERA_ZERO_DIST);
	m_flat = sqrt(m_focal_length*m_focal_length + m_horizon*m_horizon);
	m_tilt = atan2f(Preferences::GetInstance()->GetFloat("CameraHeight", CAMERA_HEIGHT), Preferences::GetInstance()->GetFloat("CameraZeroDist", CAMERA_ZERO_DIST));
}

/** \brief Get a pointer to the video processor
 *
 * The Video needs to be a parallel process so its cycles won't interfere with the iterations
 * of the Command based robot code. This GetInstance spawns a posix thread as soon as the
 * object is created. And that thread spins out on its own. The communications then happen
 * via the shared variables and a mutex semaphore pointed to by this pointer.
 */
RobotVideo* RobotVideo::GetInstance()
{
	if(!m_pInstance) {
		m_pInstance = new RobotVideo;
		// Recursion hazard!!! VideoThread() also uses this GetInstance()
		// But the second reentry should not come to this point because m_pInstance will be already defined.

		int th = pthread_create(&m_thread, NULL, VideoThread, NULL);
		// After this call above the process forks to two threads:
		// One continues here and the other goes into VideoThread()

		std::cerr << "RobotVideo thread created " << th << " Thread: " << m_thread << std::endl;
	}
	return m_pInstance;
};

/** \brief Purge the camera buffer
 *
 * The stream takes a while to start up, and because of it, images from the camera
 * buffer. We don't have a way to jump to the end of the stream to get the latest image, so we
 * run this loop as fast as we can and throw away all the old images. This wait, waits some number of seconds
 * before we are at the end of the stream, and can allow processing to begin.
 */
void PurgeBuffer(cv::VideoCapture& vcap, double fps=7.5)
{
	Timer timer;
	double start, end;
	cv::Mat frame;

	timer.Reset();
	timer.Start();
	//run in continuous loop
	while (true)
	{
		start = timer.Get();
		vcap.read(frame);
		end = timer.Get();

		if (end - start > 0.5/fps || end >= 5.0)
			break;
	}
}

/** \brief Process the list of found contours for FIRSTSTRONGHOLD
 *
 * This is the main logic for target processing in regards to FRC Stronghold game of 2016
 * The idea is to go through the list and rate each contour by the similarity with U-shaped vision target.
 * Then chose the top two by the rating since only two targets can be seen at a time.
 * This function updates the object's member data that can be queried later from outside.
 * \param contours Vector of contours. Where a contour is a Vector of Points
 */
void RobotVideo::ProcessContours(std::vector<std::vector<cv::Point>> contours) {
	// To rearrange the set of random contours into a rated list of targets
	// we're going to need a new vector that we can sort
	struct Target {
		double rating;
		std::vector<cv::Point> contour;
	};
	std::vector<struct Target> targets;

	for (std::vector<cv::Point> cont : contours)
	{
		// Only process a contour if it is big enough, otherwise it's either too far away or just a noise
		if (cv::contourArea(cont) > MIN_AREA) {
			double similarity = cv::matchShapes(stencil, cont, CV_CONTOURS_MATCH_I3, 1);

			// Less the similarity index closer the contour matches the stencil shape
			// We are interested only in very similar ones
			if (similarity < 4.0) {
				if (targets.empty()) {
					// When we just started the first contour is our best candidate
					targets.push_back({similarity, cont});
				}
				else {
					bool found = false;
					for (std::vector<struct Target>::iterator it = targets.begin(); it != targets.end(); ++it) {
						// Run through all targets we have found so far and find the position where to insert the new one
						if (similarity < it->rating) {
							targets.insert(it, {similarity, cont});
							found = true;
							break;
						}
					}
					if (!found) targets.push_back({similarity, cont});

					// If there are too many targets after the insert pop the last one
					if (targets.size() > MAX_TARGETS) targets.pop_back();
				}
			}
		}
	}

	// Now as we have the top MAX_TARGETS contours qualified as targets
	// Extract four point from each contour that describe the rectangle and store the results
	std::vector<std::vector<cv::Point>> boxes;
	std::vector<double> turns;
	for (struct Target target : targets) {
		//Extract 4 corner points assuming the blob is a rectangle, more or less horizontal
		std::vector<cv::Point> hull(4);
		hull[0] = cv::Point(10000, 10000);		// North-West
		hull[1] = cv::Point(0, 10000);			// North-East
		hull[2] = cv::Point(0, 0);				// South-East
		hull[3] = cv::Point(10000, 0);			// South-West
		for (cv::Point point : target.contour) {
			if (hull[0].x + hull[0].y > point.x + point.y) hull[0] = point;
			if (hull[1].y - hull[1].x > point.y - point.x) hull[1] = point;
			if (hull[2].x + hull[2].y < point.x + point.y) hull[2] = point;
			if (hull[3].x - hull[3].y > point.x - point.y) hull[3] = point;
		}

		// dX is the offset of the target from the frame's center to the left
		float dX = 0.5*(CAPTURE_COLS - hull[0].x - hull[1].x);
		// dY is the distance from the zenith to the target on the image
		float dY = m_zenith + 0.5*(hull[0].y + hull[1].y - CAPTURE_ROWS);
		// The real azimuth to the target is on the horizon, so scale it accordingly
		float azimuth = dX * ((m_zenith + m_horizon) / dY);
		double real_angle = atan2(azimuth, m_flat);

		turns.push_back(real_angle * 180/M_PI + Preferences::GetInstance()->GetFloat("CameraBias",0));
		boxes.push_back(hull);
	}

	if (MAX_TARGETS == 2 && boxes.size() == 2) {
		if (boxes.front().front().x > boxes.back().front().x) {
			boxes.front().swap(boxes.back());
			double tmp = turns.front();
			turns.front() = turns.back();
			turns.back() = tmp;
		}
	}

	// To avoid misreading of our data from other threads we lock our mutex
	// before updating the shared data and then unlock it when done.
	mutex_lock();
	m_boxes = boxes;
	m_turns = turns;
	mutex_unlock();
}

float RobotVideo::GetDistance(size_t i, Target_side side)
{
	// Distance by the height. Farther an object with known height lower it appears on the image.
	// The real height of the target is 97 inches.
	// Camera is 12 inches above the floor.

	size_t tip;
	switch (side) {
	case kLeft:
		tip = 0;
		break;
	case kRight:
		tip = 1;
		break;
	default:
		// This function can call itself recursively to get the distance to the middle as the average of two sides
		return (GetDistance(i, kLeft) + GetDistance(i, kRight)) / 2;
	}

	float dx = CAPTURE_COLS/2 - m_boxes[i][tip].x;
	float dy = m_zenith - CAPTURE_ROWS/2 + m_boxes[i][tip].y;
	float dh = sqrt(dx*dx + dy*dy) - m_zenith;
	return Preferences::GetInstance()->GetFloat("CameraHeight", CAMERA_HEIGHT)
			/ tanf(m_tilt - atan2f(dh, Preferences::GetInstance()->GetFloat("CameraFocal", CAPTURE_FOCAL)));
}

float RobotVideo::GetTurn(size_t i)
{
	return m_turns[i];
}

void RobotVideo::Run()
{
	cv::VideoCapture capture;

	//open the video stream and make sure it's opened
	//We specify desired frame size and fps in constructor
	//Camera must be able to support specified framesize and frames per second
	//or this will set camera to defaults
	int count=1;
	while (!capture.open(CAPTURE_PORT, CAPTURE_COLS, CAPTURE_ROWS, CAPTURE_FPS))
	{
		std::cerr << "Error connecting to camera stream, retrying " << count<< std::endl;
		count++;
		usleep(5 * 1000000);
	}

	//After Opening Camera we need to configure the returned image setting
	//all opencv v4l2 camera controls scale from 0.0 to 1.0
	capture.set(CV_CAP_PROP_EXPOSURE, 0);
	capture.set(CV_CAP_PROP_BRIGHTNESS, 0);
	capture.set(CV_CAP_PROP_CONTRAST, 0);


	//set true to indicate we're connected and the thread is working.
	m_connected = true;
	PurgeBuffer(capture, CAPTURE_FPS);

	while(true) {
		cv::Mat Im;
		cv::Mat hsvIm;
		cv::Mat BlobIm;
		cv::Mat bw;
		Timer timer;

		timer.Reset();
		timer.Start();

		capture >> Im;
		if (Im.empty()) {
			std::cerr << " Error reading from camera" << std::endl;
			usleep(5 * 1000000);
			continue;
		}

		double t_start = timer.Get();
		mutex_lock();
		bool display = m_display;
		InitVariables();
		mutex_unlock();

		if(m_idle) {
			// Don't do any processing but sleep for a half of the camera's FPS time.
			useconds_t sleeptime = 1000000 / CAPTURE_FPS;
			if (display) {
				std::ostringstream oss;
				oss << "Time: " << timer.Get();
				cv::putText(Im, oss.str(), cv::Point(20,30), 1, 1, cv::Scalar(0, 200,255), 1);
				cv::putText(Im, "Idle", cv::Point(20,CAPTURE_ROWS-40), 1, 1, cv::Scalar(0, 255,100), 1);
				cv::imwrite(IMG_FILE_NAME, Im);
				m_display = false;
				sleeptime = 1000000 / CAPTURE_FPS / 4;
			}
			usleep(sleeptime);
			continue;
		}

		// Convert and filter the image to extract only green pixels
		cv::cvtColor(Im, hsvIm, CV_BGR2HSV);
		cv::inRange(hsvIm, BlobLower, BlobUpper, BlobIm);
		BlobIm.convertTo(bw, CV_8UC1);

		// Extract Contours. Thanks OpenCV for all the math
		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(bw, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

		// We have a separate function specifically designed to process contours for FIRSTSTRONGHOLD
		ProcessContours(contours);

		if (display) {
			// This step is not functional, it's just for visibility.
			// No functional calculations are done within this block.

			// Draw pink boxes around detected targets
			for (std::vector<cv::Point> box : m_boxes) {
				std::vector<cv::Point> crosshair;
				crosshair.push_back(cv::Point(box[0].x-5, box[0].y-5));
				crosshair.push_back(cv::Point(box[1].x+5, box[1].y-5));
				crosshair.push_back(cv::Point(box[2].x+5, box[2].y+5));
				crosshair.push_back(cv::Point(box[3].x-5, box[3].y+5));
				cv::polylines(Im, crosshair, true, cv::Scalar(260, 0, 255),2);
			}

			int x =  CAPTURE_COLS/2.0 +
					Preferences::GetInstance()->GetFloat("CameraFocal", CAPTURE_FOCAL) * tan((M_PI/180) *
					Preferences::GetInstance()->GetFloat("CameraBias", 0));

			cv::Scalar colorCross;
			if ( (m_boxes.size() > 0 and m_boxes[0][1].y + m_boxes[0][0].y == CAPTURE_ROWS)
				or (m_boxes.size() > 1 and m_boxes[1][1].y + m_boxes[1][0].y == CAPTURE_ROWS) )
			{
				colorCross = cv::Scalar(100,100,255);
			}
			else {
				colorCross = cv::Scalar(0,0,160);
			}

			cv::line(Im,cv::Point(x,40),cv::Point(x,CAPTURE_ROWS-40),colorCross,1);
			cv::line(Im,cv::Point(40,CAPTURE_ROWS/2),cv::Point(CAPTURE_COLS-40,CAPTURE_ROWS/2),colorCross,1);

			std::ostringstream oss1, oss2;
			cv::Scalar ossColor(260, 0, 255);
			if (HaveHeading() > 0) {
				oss1 << "Turn: ";
				oss2 << "Dist: ";
				if (HaveHeading() > 1) {
					oss1 << GetTurn(0) << " : " << GetTurn(1);
					oss2 << GetDistance(0) << " : " << GetDistance(1);
				}
				else {
					oss1 << GetTurn();
					oss2 << GetDistance();
				}
			}
			else {
				oss1 << "No target";
				oss2 << "No target";
				ossColor = cv::Scalar(0, 100,255);
			}
			cv::putText(Im, oss1.str(), cv::Point(20,CAPTURE_ROWS-32), 1, 1, ossColor, 1);
			cv::putText(Im, oss2.str(), cv::Point(20,CAPTURE_ROWS-16), 1, 1, ossColor, 1);

			std::ostringstream oss;
			oss << 1000.0*(timer.Get() - t_start) << " ms, " << 1.0 / timer.Get() << " fps";
			cv::putText(Im, oss.str(), cv::Point(20,30), 1, 1, cv::Scalar(0, 200,255), 1);

			cv::imwrite(IMG_FILE_NAME, Im);
			m_display = false;
		}
	}
}

/** \brief The video thread entry point
 *
 * POSIX Threads create function requires a standalone (not a class method) function
 * as the new thread's starting point. This is an implementation of such.
 * We also made the class's Run() method protected and declared this VideoThread()
 * function a friend so nothing else can accidentally call the Run() method.
 */
void *VideoThread(void *param)
{
	RobotVideo *p = RobotVideo::GetInstance();
	p->Run();
	// The "Run" above should never return
	return NULL;
}

