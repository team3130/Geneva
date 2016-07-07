#ifndef CHASSIS_H
#define CHASSIS_H

#include <WPILib.h>
#include <AHRS.h>
#include "Commands/Subsystem.h"
#include "RobotMap.h"

/** Robot's main chassis, or drivetrain.
 *
 * This must be a singleton class because a robot usually can have only one chassis.
 * The class manages all the driving motors and all methods of driving itself.
 * All activities with the drivetrain must be done via its public methods.
 */
class Chassis: public PIDSubsystem
{
	 /* Wheel sprockets 22
	  * Encoder shaft sprockets: 15
	  * Wheel diameter: 7.625
	  * Calibrating ratio: 0.955
	  */
	static constexpr double InchesPerRev = 0.955 * M_PI * 7.625 * 15 / 22;
private:
	static Chassis* m_pInstance;
	RobotDrive *m_drive;
	Solenoid* m_shifter;
	CANTalon* m_leftMotorFront;
	CANTalon* m_leftMotorRear;
	CANTalon* m_rightMotorFront;
	CANTalon* m_rightMotorRear;
	AHRS* m_navX;

	bool m_bShiftedLow;
	double moveSpeed;
	double prevAbsBias;
	bool m_onPID;
	bool m_onGyro;
	bool m_bNavXPresent;

	Chassis();
	Chassis(Chassis const&);
	Chassis& operator=(Chassis const&);
public:
	static Chassis* GetInstance();
	void InitDefaultCommand();
	void Drive(double move, double turn, bool squaredInputs = false);
	void DriveArcade(double move, double turn, bool squaredInputs = false);
	void Shift(bool shiftDown);
	bool GetGearState(){return m_bShiftedLow;}

	virtual double ReturnPIDInput();
	virtual void UsePIDOutput(double outputAngle);
	double GetSpeedL();
	double GetSpeedR();
	double GetSpeed();
	double GetDistanceL();
	double GetDistanceR();
	double GetDistance();
	double GetPIDError() {return GetSetpoint() - GetPosition();};
	void SetPIDValues();
	void ResetEncoders();
	double GetAngle(bool forceGyro=false);
	void HoldAngle(double angle = 0, bool gyro = false);
	void ReleaseAngle();
	void DriveStraight(double move) { moveSpeed = move; };
	void SetGyroMode(bool enabled)	{if(!m_onPID) m_onGyro = enabled;};	//Prevent changing angle type mid turn or angle hold.
};

#endif
