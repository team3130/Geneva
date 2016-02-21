/*
 * RelayDevice.h
 *
 *  Created on: Apr 5, 2015
 *      Author: kma1660
 */

#ifndef SRC_RIPTIDERECORDER_DEVICES_RELAYDEVICE_H_
#define SRC_RIPTIDERECORDER_DEVICES_RELAYDEVICE_H_

#include "../Device.h"
#include <string>
#include "WPILib.h"

class RelayDevice : public Device{
public:
	RelayDevice(std::string x,Relay* r);
	virtual float get();
	virtual void set(float x);
private:
	Relay* relay;
};

#endif /* SRC_RIPTIDERECORDER_DEVICES_RELAYDEVICE_H_ */
