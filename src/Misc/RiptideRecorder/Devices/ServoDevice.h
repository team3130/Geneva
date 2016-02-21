/*
 * ServoDevice.h
 *
 *  Created on: Apr 5, 2015
 *      Author: kma1660
 */

#ifndef SRC_RIPTIDERECORDER_DEVICES_SERVODEVICE_H_
#define SRC_RIPTIDERECORDER_DEVICES_SERVODEVICE_H_

#include "../Device.h"
#include <string>
#include "WPILib.h"

class ServoDevice : public Device{
public:
	ServoDevice(std::string n,Servo* s);
	virtual float get();
	virtual void set(float x);
private:
	Servo* servo;
};

#endif /* SRC_RIPTIDERECORDER_DEVICES_SERVODEVICE_H_ */
