/*
 * ServoDevice.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: kma1660
 */

#include "ServoDevice.h"

ServoDevice::ServoDevice(std::string n,Servo* s) : Device(n){
	servo = s;
}
float ServoDevice::get() {
	return servo->Get();
}
void ServoDevice::set(float x) {
	servo->Set(x);
}
