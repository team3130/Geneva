/*
 * Device.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: kma1660
 */
#include "Device.h"

Device::Device(std::string x) {
	name=x;
}
Device::~Device() {

}
void Device::SetName(std::string n) {
	name = n;
}
std::string Device::GetName() {
	return name;
}
