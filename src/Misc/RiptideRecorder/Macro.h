/*
 * Macro.h
 *
 *  Created on: Apr 4, 2015
 *      Author: kma1660
 */

#ifndef MACRO_H_
#define MACRO_H_
#include "Device.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "WPILib.h"

class Macro {
public:
	Macro(std::vector<Device*> devices);
	Macro(std::vector<Device*> devices,std::vector<Subsystem* > s);
	void Reset();
	void Record();
	void PlayReset();
	void PlayBack();
	void WriteFile(std::string filename);
	void ReadFile(std::string filename);

	void StartRecording();
	void StopRecording();

	void StartPlay();
	void StopPlay();

	bool IsFinished();

	Command* NewPlayCommand();
	Command* NewPlayFileCommand(std::string FileName);
	Command* NewRecordCommand();
	Command* NewRecordFileCommand(std::string FileName);

	std::vector<Subsystem * > subsystems;
private:
	unsigned int length;
	unsigned int position;

	std::map<Device * , std::vector<float> >::iterator it;
	std::map <Device * , std::vector<float> > Values;
};

#endif /* MACRO_H_ */
