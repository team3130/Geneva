#include <WPILib.h>
#include "Subsystems/IntakeWheel.h"
#include "Subsystems/IntakeHorizontal.h"
#include "Subsystems/IntakeVertical.h"
#include "Subsystems/IntakePin.h"
#include "Subsystems/Catapult.h"
#include "Subsystems/CatapultFire.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/Climber.h"
#include "AutonCommands/1BallReturn.h"
#include "AutonCommands/1BallAuton.h"
#include "AutonCommands/PickUpAuton.h"
#include "AutonCommands/PickUpReturn.h"
#include "AutonCommands/Stop2BallAuton.h"
#include "AutonCommands/NoAuton.h"
#include "AutonCommands/2BallAuton.h"
#include "AutonCommands/1BallAutonDumb.h"
#include "Commands/RobotSensors.h"
#include "Commands/CameraFeed.h"
#include "Subsystems/Blinkies.h"
#include "Subsystems/CatStopCalculations.h"


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
		IntakePin::GetInstance();
		Climber::GetInstance();
		Catapult::GetInstance();
		CatapultFire::GetInstance();
		CatStopCalculations::GetInstance();
		//Creates Radio Buttons for selection of Auton modes, include and AddObject() for each
		//Autonomous Mode being added
		autonChooser = new SendableChooser();
		autonChooser->AddDefault("One Ball Auton Time", new OneBallAutonDumb());
		autonChooser->AddObject("One Ball Auton", new OneBallAuton());
		autonChooser->AddObject("No Auton", new NoAuton());
		autonChooser->AddObject("One Ball Return", new OneBallReturn());
		autonChooser->AddObject("Pick Up Ball Auton", new PickUpAuton());
		autonChooser->AddObject("Pick Up Ball Return Auton", new PickUpReturn());
		autonChooser->AddObject("Stop Two Ball Auton",new Stop2BallAuton());
		autonChooser->AddObject("Two Ball Auton", new TwoBallAuton());
		SmartDashboard::PutData("Autonomous Choices", autonChooser);
		lw = LiveWindow::GetInstance();
	}
	
	void DisabledInit()
	{
		// printf("Default %s() method... Overload me!\n", __FUNCTION__);
		Blinkies::PutCommand("roundEnd");
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

		//Set Default positions for the intake axis upon telop enable.
		IntakeHorizontal::GetInstance()->Actuate(true);
		IntakeVertical::GetInstance()->Actuate(false);
		IntakePin::GetInstance()->Actuate(false);
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

