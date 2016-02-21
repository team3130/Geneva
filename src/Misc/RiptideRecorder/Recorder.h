/*
 * Recorder.h
 *
 *  Created on: Apr 2, 2015
 *      Author: kma1660
 */

#ifndef RECORDER_H_
#define RECORDER_H_

#include "Device.h"
#include "Devices/SpeedControllerDevice.h"
#include "Devices/RelayDevice.h"
#include "Devices/SolenoidDevice.h"
#include "Devices/DoubleSolenoidDevice.h"
#include "Devices/ServoDevice.h"

#include "WPILib.h"
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Macro.h"

class Recorder {
	public:
		Recorder();

		void AddDevice(Device* dev);
		void AddDevice(std::string n,SpeedController* c);
		void AddDevice(std::string n,Relay* r);
		void AddDevice(std::string n, Solenoid* s);
		void AddDevice(std::string n, DoubleSolenoid* ds);
		void AddDevice(std::string n, Servo* s);
		void AddSubsystem(Subsystem* s);

		Macro* macro();
		static Recorder* GetInstance();
	private:
		std::vector<Device *> devices;
		std::vector<Subsystem *> subsystems;
		static Recorder* instance;
};

#endif /* RECORDER_H_ */
