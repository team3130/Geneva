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
	bool m_lowGear;
	bool m_setShift;

public:
	AutonDriveToPoint(bool setShift=true);
	~AutonDriveToPoint();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetParam(double travelDistance, double angle=0, double speed=0.5, double tolerance=0.5, bool lowGear = false);

	void SetPIDValues();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
};

#endif
