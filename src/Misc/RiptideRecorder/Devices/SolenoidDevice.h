/*
 * SolenoidDevice.h
 *
 *  Created on: Apr 5, 2015
 *      Author: kma1660
 */

#ifndef SRC_RIPTIDERECORDER_DEVICES_SOLENOIDDEVICE_H_
#define SRC_RIPTIDERECORDER_DEVICES_SOLENOIDDEVICE_H_

#include "../Device.h"
#include <string>
#include "WPILib.h"

class SolenoidDevice : public Device{
public:
	SolenoidDevice(std::string x,Solenoid* s);
	virtual float get();
	virtual void set(float x);
private:
	Solenoid* solenoid;
};

#endif /* SRC_RIPTIDERECORDER_DEVICES_SOLENOIDDEVICE_H_ */
