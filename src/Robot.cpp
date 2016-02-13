#include <WPILIB.h>
#include "Subsystems/IntakeWheel.h"
#include "Subsystems/IntakeHorizontal.h"
#include "Subsystems/IntakeVertical.h"
#include "Subsystems/Catapult.h"
#include "Subsystems/CatapultFire.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/Climber.h"
#include "AutonCommands/2BallAuton.h"
#include "Commands/RobotSensors.h"
#include "Commands/CameraFeed.h"


class Robot: public IterativeRobot
{
private:
	Command *autonomousCommand;
	SendableChooser* autonChooser;
	LiveWindow *lw;
	Compressor* compressor;
	Command *robotSensors;
	CameraFeed *cameraFeed;


	void RobotInit()
	{
		compressor = new Compressor(CAN_PNMMODULE);
		compressor->Start();
		robotSensors = new RobotSensors();
		robotSensors->Start();
		cameraFeed = new CameraFeed();
		cameraFeed->Start();
		// Create a single static instance of all of your subsystems. The following
		// line should be repeated for each subsystem in the project.
		Chassis::GetInstance();
		IntakeWheel::GetInstance();
		IntakeHorizontal::GetInstance();
		IntakeVertical::GetInstance();
		Climber::GetInstance();
		Catapult::GetInstance();
		CatapultFire::GetInstance();
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

