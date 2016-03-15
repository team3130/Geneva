#ifndef AUTON_DRIVE_TO_POINT_H
#define AUTON_DRIVE_TO_POINT_H

#include <WPILib.h>

class AutonDriveToPoint: public PIDCommand
{
private:
	Timer* timer;
	double m_speed;
	double m_setPoint;
	double m_angle;
	double m_threshold;
	double m_timeout;
	bool m_lowGear;

public:
	AutonDriveToPoint();
	~AutonDriveToPoint();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetParam(double travelDistance, double angle=0, double speed=0.5, double tolerance=0.5, double timeout=0, bool lowGear = false);

	double ReturnPIDInput();
	void UsePIDOutput(double output);
};

#endif
