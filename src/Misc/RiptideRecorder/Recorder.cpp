/*
 * Recorder.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: kma1660
 */

#include "Recorder.h"

Recorder* Recorder::instance = NULL;

Recorder::Recorder() {

}
void Recorder::AddDevice(Device* dev) {
	devices.push_back(dev);
}
void Recorder::AddDevice(std::string n,SpeedController* c) {
	AddDevice(new SpeedControllerDevice(n,c));
}
void Recorder::AddDevice(std::string n,Relay* r) {
	AddDevice(new RelayDevice(n,r));
}
void Recorder::AddDevice(std::string n,Solenoid* s) {
	AddDevice(new SolenoidDevice(n,s));
}
void Recorder::AddDevice(std::string n,DoubleSolenoid* ds) {
	AddDevice(new DoubleSolenoidDevice(n,ds));
}
void Recorder::AddDevice(std::string n, Servo* s) {
	AddDevice(new ServoDevice(n,s));
}
void Recorder::AddSubsystem(Subsystem* s) {
	subsystems.push_back(s);
}
Macro* Recorder::macro () {
	return new Macro(this->devices,this->subsystems);
}
Recorder* Recorder::GetInstance() {
	if (!instance)
			instance = new Recorder;

	return instance;
}
