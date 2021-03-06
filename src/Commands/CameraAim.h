#ifndef CameraAim_H
#define CameraAim_H

#include "WPILib.h"

class LocationRecord
{
public:
	double time;
	double dist;
};

class CameraAim: public Command
{
public:
	enum Target_side {
		kMiddle,
		kLeft,
		kRight
	};
	static constexpr double MAX_ANGULAR_V = 2; //!<- degrees per second
	static constexpr double AIM_COOLDOWN = 0.25; //!<- seconds to sit still before acquiring a new visual

	CameraAim(Target_side side, JoystickButton *button, bool auton=false);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetParam(Target_side kSide);

private:
	Timer location_timer;
	Timer frame_timer;
	Timer cycle_timer;
	Target_side m_side;
	JoystickButton *m_button;
	std::queue<LocationRecord> m_locationQueue;
	double m_prevAngle;
	double m_target;
	bool m_gotLock;
	bool m_gotVisual;
	bool m_auton;
};

#endif
