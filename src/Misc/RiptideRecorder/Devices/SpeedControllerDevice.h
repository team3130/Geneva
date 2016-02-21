/*
 * SpeedControllerDevice.h
 *
 *  Created on: Apr 5, 2015
 *      Author: kma1660
 */

#ifndef SRC_RIPTIDERECORDER_DEVICES_SPEEDCONTROLLERDEVICE_H_
#define SRC_RIPTIDERECORDER_DEVICES_SPEEDCONTROLLERDEVICE_H_

#include "../Device.h"
#include <string>
#include "WPILib.h"

class SpeedControllerDevice : public Device{
public:
	SpeedControllerDevice(std::string x,SpeedController* c);
	virtual float get();
	virtual void set(float x);
private:
	SpeedController* ctrl;
};

#endif /* SRC_RIPTIDERECORDER_DEVICES_SPEEDCONTROLLERDEVICE_H_ */
