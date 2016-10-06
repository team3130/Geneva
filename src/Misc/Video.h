/*
 * Video.h
 *
 *  Created on: Jan 11, 2016
 *      Author: Mikhail Kyraha
 */

#ifndef SRC_VIDEO_H_
#define SRC_VIDEO_H_

#include "opencv2/core/core.hpp"
#include <pthread.h>
#include <unistd.h>
#include <list>

class RobotVideo {
public:
	enum Target_side {
		kMiddle,
		kLeft,
		kRight
	};
	static const char* IMG_FILE_NAME;
	static constexpr double CAPTURE_FPS = 20;
	static constexpr double CAPTURE_FOCAL = 370.9;
	static constexpr double CAMERA_OFFSET = 7.5; //!<- Offset of the camera from the catapult
	static constexpr double CAMERA_HEIGHT = 85; //!<- Tower height is 97" and the camera is 12" above the floor
	static constexpr double CAMERA_ZERO_DIST = 130; //!<- Tower height is 97" and the camera is 12" above the floor

	//static const int CAPTURE_COLS=640, CAPTURE_ROWS=480;
	static const int CAPTURE_COLS=424, CAPTURE_ROWS=240;
	static const int CAPTURE_PORT=0;
	static const int MIN_AREA=135; // Min area in pixels, 3*(25+40+25) is a rough estimate
	static const int MAX_TARGETS=2;

private:
	static RobotVideo* m_pInstance;
	static pthread_t m_thread;
	pthread_mutex_t m_mutex = PTHREAD_MUTEX_INITIALIZER;
	bool m_connected, m_idle;
	std::vector<std::vector<cv::Point>> m_boxes;
	std::vector<double> m_turns;

	// These could be constants if the "CameraZeroDist" was a constant but it is a preset stored in the Preferences.
	// So these semi-dynamic variables should be pre-calculated and then can be reused.
	float m_focal_length;
	float m_zenith; //!<- Distance from the frame center to the zenith in focal length units (pixels)
	float m_horizon; //!<- Distance from the frame center to the horizon in focal length units (pixels)
	float m_flat; //!<- Distance from the lens to the horizon in focal length units
	float m_tilt; //!<- The pitch angle of the camera, tilt, in radians

	void ProcessContours(std::vector<std::vector<cv::Point>> contours);
	void InitVariables();

	// Hide constructors because singleton
	RobotVideo();
	RobotVideo(RobotVideo const&);
	RobotVideo &operator =(RobotVideo const&);
public:
	bool m_display;
	int mutex_lock() { return pthread_mutex_lock(&m_mutex); };
	int mutex_unlock() { return pthread_mutex_unlock(&m_mutex); };
	static RobotVideo* GetInstance();

	// These guys need mutex locked but user should do that so can wrap them in a bunch
	size_t HaveHeading() {return m_boxes.size();};
	float GetTurn(size_t i=0);
	float GetDistance(size_t i=0, Target_side side=kMiddle);

	// Reading/writing a bool is atomic, no need in mutex lock
	void Enable() {m_idle = false;};
	void Disable() {m_idle = true;};

protected:
	void Run();

	friend void *VideoThread(void *param);
};

void *VideoThread(void *param);

#endif /* SRC_VIDEO_H_ */
