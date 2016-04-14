#include "Misc/Video.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <algorithm>
#include <WPILib.h>
#include <Timer.h>

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
		// But the second reentry should not come to this point because m_pInstance will be defined.
		int th = pthread_create(&m_thread, NULL, VideoThread, NULL);
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

void RobotVideo::ProcessContours(std::vector<std::vector<cv::Point>> contours) {
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

		float turn = 0.5*(hull[0].x + hull[1].x);
		double real_angle = atan2(CAPTURE_COLS/2.0 - turn, Preferences::GetInstance()->GetFloat("CameraFocal",CAPTURE_FOCAL));

		turns.push_back(real_angle * 180/M_PI + Preferences::GetInstance()->GetFloat("CameraBias",0));
		boxes.push_back(hull);
	}

	if(MAX_TARGETS==2 && boxes.size()==2) {
		if(boxes.front().front().x > boxes.back().front().x) {
			boxes.front().swap(boxes.back());
		}
	}

	mutex_lock();
	m_boxes = boxes;
	m_turns = turns;
	mutex_unlock();
}

float RobotVideo::GetDistance(size_t i)
{
	// Distance by the height. The real height of the target is 97 inches.
	float dy = (m_boxes[i][1].y + m_boxes[i][0].y - CAPTURE_ROWS)/2.0;
	float tower = 97 - Preferences::GetInstance()->GetFloat("CameraHeight", 12);
	float alpha = atan2f(tower, Preferences::GetInstance()->GetFloat("CameraZeroDist", 130));
	return tower / tanf(alpha - atan2f(dy, CAPTURE_FOCAL));
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
	capture.set(CV_CAP_PROP_EXPOSURE_ABSOLUTE, 0);
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

		cv::cvtColor(Im, hsvIm, CV_BGR2HSV);
		cv::inRange(hsvIm, BlobLower, BlobUpper, BlobIm);

		//Extract Contours
		BlobIm.convertTo(bw, CV_8UC1);

		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(bw, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

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

			int x =  CAPTURE_COLS/2.0 + CAPTURE_FOCAL * tan((M_PI/180)*Preferences::GetInstance()->GetFloat("CameraBias", 0));

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

void *VideoThread(void *param)
{
	RobotVideo *p = RobotVideo::GetInstance();
	p->Run();
	// The "Run" above should never return
	return NULL;
}

