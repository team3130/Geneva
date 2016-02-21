/*
 * DoubleSolenoidDevice.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: kma1660
 */

#include "DoubleSolenoidDevice.h"

DoubleSolenoidDevice::DoubleSolenoidDevice(std::string n,DoubleSolenoid* ds) : Device (n) {
	doublesolenoid = ds;
}
float DoubleSolenoidDevice::get() {
	switch (doublesolenoid->Get()) {
		case DoubleSolenoid::Value::kForward:
			return 1;
		case DoubleSolenoid::Value::kReverse:
			return -1;
		default:
			return 0;
	}
}
void DoubleSolenoidDevice::set(float x) {
	switch ( (int) x) {
		case 1:
			doublesolenoid->Set(DoubleSolenoid::Value::kForward);
			break;
		case -1:
			doublesolenoid->Set(DoubleSolenoid::Value::kReverse);
			break;
		default:
			doublesolenoid->Set(DoubleSolenoid::Value::kOff);
			break;
	}
}
