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

class DataSet : public std::list<float> {
public:
	float GetMedian();
};


class RobotVideo {
public:
	static const char* IMG_FILE_NAME;
	static constexpr double CAPTURE_FPS = 20;
	static constexpr double CAPTURE_FOCAL = 290;
	static constexpr double CAMERA_OFFSET = 7.5; //!<- Offset of the camera from the catapult

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
	size_t m_sizeLocation, m_sizeHeading;
	std::vector<std::vector<cv::Point>> m_boxes;
	std::vector<cv::Vec3f> m_locations;
	std::vector<double> m_turns;

	size_t ProcessContours(std::vector<std::vector<cv::Point>> contours);

	// Hide constructors because singleton
	RobotVideo();
	RobotVideo(RobotVideo const&);
	RobotVideo &operator =(RobotVideo const&);
public:
	bool m_display;
	int mutex_lock() { return pthread_mutex_lock(&m_mutex); };
	int mutex_unlock() { return pthread_mutex_unlock(&m_mutex); };
	static RobotVideo* GetInstance();

	void SetLocationQueueSize(size_t s) {mutex_lock(); m_sizeLocation=s; mutex_unlock();};
	void SetHeadingQueueSize(size_t s) {mutex_lock(); m_sizeHeading=s; mutex_unlock();};

	// These guys need mutex locked but user should do that so can wrap them in a bunch
	size_t HaveHeading() {return m_boxes.size();};
	float GetTurn(size_t i=0) {return m_turns[i];};
	float GetDistance(size_t i=0);

	// Reading/writing a bool is atomic, no need in mutex lock
	void Enable() {m_idle = false;};
	void Disable() {m_idle = true;};

protected:
	void Run();

	friend void *VideoThread(void *param);
};

void *VideoThread(void *param);

#endif /* SRC_VIDEO_H_ */
