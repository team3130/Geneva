#include <WPILIB.h>
#include "Subsystems/Chassis.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/WinchLock.h"
#include "AutonCommands/2BallAuton.h"

class Robot: public IterativeRobot
{
private:
	Command *autonomousCommand;
	SendableChooser* autonChooser;
	LiveWindow *lw;
	Compressor* compressor;

	void RobotInit()
	{
		compressor = new Compressor(PNM_MODULE);
		compressor->Start();
		// Create a single static instance of all of your subsystems. The following
		// line should be repeated for each subsystem in the project.
		ChassisSubsystem::GetInstance();
		IntakeSubsystem::GetInstance();
		ShooterSubsystem::GetInstance();
		WinchLockSubsystem::GetInstance();
		//Creates Radio Buttons for selection of Auton modes, include and AddObject() for each
		//Autonomous Mode being added
		autonChooser = new SendableChooser();
		autonChooser->AddDefault("No Auton", nullptr);
		autonChooser->AddObject("Two Ball Auton", new TwoBallAuton());
		SmartDashboard::PutData("Autonomous Choices", autonChooser);
		lw = LiveWindow::GetInstance();
	}
	
	void DisabledInit()
	{
		// printf("Default %s() method... Overload me!\n", __FUNCTION__);
	}

	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit()
	{
		autonomousCommand = (Command *)autonChooser->GetSelected();
		if(autonomousCommand != nullptr)
		{
			autonomousCommand->Start();
		}

	}

	void AutonomousPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit()
	{
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (autonomousCommand !=nullptr)
			autonomousCommand->Cancel();
	}

	void TeleopPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);

