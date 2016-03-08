#ifndef CameraAim_H
#define CameraAim_H

#include "WPILib.h"

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

	CameraAim(Target_side side=kLeft);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	Timer frame_timer;
	Timer cycle_timer;
	Target_side m_side;
	double m_prevAngle;
	bool m_gotVisual;
};

#endif
