/*
 * SolenoidDevice.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: kma1660
 */

#include "SolenoidDevice.h"

SolenoidDevice::SolenoidDevice(std::string x,Solenoid* s) : Device(x) {
	solenoid = s;
}
float SolenoidDevice::get() {
	return (float) solenoid->Get();
}
void SolenoidDevice::set(float x) {
	solenoid->Set( (bool) x);
}
