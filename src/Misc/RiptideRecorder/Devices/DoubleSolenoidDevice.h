/*
 * DoubleSolenoidDevice.h
 *
 *  Created on: Apr 5, 2015
 *      Author: kma1660
 */

#ifndef SRC_RIPTIDERECORDER_DEVICES_DOUBLESOLENOIDDEVICE_H_
#define SRC_RIPTIDERECORDER_DEVICES_DOUBLESOLENOIDDEVICE_H_

#include "../Device.h"
#include <string>
#include "WPILib.h"

class DoubleSolenoidDevice : public Device {
public:
	DoubleSolenoidDevice(std::string n,DoubleSolenoid* ds);
	virtual float get();
	virtual void set(float x);
private:
	DoubleSolenoid* doublesolenoid;
};

#endif /* SRC_RIPTIDERECORDER_DEVICES_DOUBLESOLENOIDDEVICE_H_ */
