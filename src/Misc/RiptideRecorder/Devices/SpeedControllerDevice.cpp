/*
 * SpeedControllerDevice.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: kma1660
 */

#include "SpeedControllerDevice.h"

SpeedControllerDevice::SpeedControllerDevice(std::string x,SpeedController* c) : Device(x){
	ctrl = c;

}
float SpeedControllerDevice::get() {
	return ctrl->Get();
}
void SpeedControllerDevice::set(float x) {
	ctrl->Set(x);
}
