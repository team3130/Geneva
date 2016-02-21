/*
 * RelayDevice.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: kma1660
 */

#include "RelayDevice.h"

RelayDevice::RelayDevice(std::string x,Relay* r) : Device(x) {
	relay = r;
}
float RelayDevice::get() {
	switch (relay->Get()) {
		case Relay::Value::kOn:
			return 2;
		case Relay::Value::kForward:
			return 1;
		case Relay::Value::kReverse:
			return -1;
		default:
			return 0;
	}
}
void RelayDevice::set(float x) {
	switch ((int) x) {
		case 2:
			relay->Set(Relay::Value::kOn);
			break;
		case 1:
			relay->Set(Relay::Value::kForward);
			break;
		case -1:
			relay->Set(Relay::Value::kReverse);
			break;
		default:
			relay->Set(Relay::Value::kOff);
	}
}
