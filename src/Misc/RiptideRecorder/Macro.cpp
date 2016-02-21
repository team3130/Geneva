/*
 * Macro.cpp
 *
 *  Created on: Apr 4, 2015
 *      Author: kma1660
 */

#include "Macro.h"
#include "Commands/RecordCommand.h"
#include "Commands/PlayBackCommand.h"
#include "Commands/PlayBackFileCommand.h"
#include "Commands/RecordFileCommand.h"

Macro::Macro(std::vector<Device*> devices) {
	for(std::vector<Device*>::iterator dev = devices.begin(); dev != devices.end(); ++dev) {
		Values[*dev].clear();
	}
	length = 0;
	position = 0;

};
Macro::Macro(std::vector<Device*> devices,std::vector<Subsystem* > s) : Macro(devices) {
	subsystems = s;
}
//Removes in memory loaded recording and resets playback to position zero
void Macro::Reset() {
	for (it = Values.begin(); it != Values.end(); it++) {
		it->second = std::vector<float> ();
	}
	length = 0;
	PlayReset();
}
//Resets position to zero so play back will start over
void Macro::PlayReset() {
	position = 0;
}
//Records an instant of all devices
void Macro::Record() {
	for (it = Values.begin(); it != Values.end(); it++) {
		it->second.push_back(it->first->get());
	}
	length++;
}
//Plays back one instant of devices and increments play back position
void Macro::PlayBack() {
	if (position >= length) return;
	for (it = Values.begin(); it != Values.end(); it++) {
		if (position >= it->second.size()) {
			it->first->set(0);
			continue;
		}
		it->first->set(it->second[position]);
	}
	position++;
}
//Writes the current in memory recording to the file at filename in CSV format, blocks
void Macro::WriteFile(std::string filename) {
	 std::ofstream file;
	 file.open(filename.c_str());
	 if (file.is_open()) {
		 //Writes the heading line with the device names, so can be matched on file readback
		 for (it = Values.begin(); it != Values.end(); it++) {
			 file << it->first->GetName();
			if (it != --Values.end()) file << ",";
		 }
		 file << "\n";

		 //Writes a new line for the in memory values at each recorded instant in the order the heading establishes
		 for (unsigned int i = 0; i<length;i++) {
			 for (it = Values.begin(); it != Values.end(); it++) {
				 if (i >= it->second.size()) {
					 file << 0;
				 }
				 else file << it->second[i];

				 if (it != --Values.end()) file << ",";
			}
			file << "\n";
		}
		file.close();
	 }
}
//Resets the in memory recording and replaces it with the recording located at the file at filename
void Macro::ReadFile(std::string filename) {
	std::ifstream file;
	file.open(filename.c_str());
	if (file.is_open()) {
		std::string line;
		std::string delimiter = ",";
		std::string token;
		size_t pos = 0;
		Reset();

		std::vector<Device*> list;

		//Get the first line to establish the list of devices
		std::getline(file,line);
		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = line.substr(0, pos);
			list.push_back(NULL);
			for (it = Values.begin(); it != Values.end(); it++) if (token == it->first->GetName()) {
				list.back() = it->first;
				break;
			};
		    line.erase(0, pos + delimiter.length());
		}

		//Grab last
		list.push_back(NULL);
		for (it = Values.begin(); it != Values.end(); it++) if (line == it->first->GetName()) {
			list.back() = it->first;
			break;
		};

		//Now, for each line append value to each device
		unsigned int i;
		length = 0;
		while (std::getline(file,line)) {
			length++;
			i = 0;
			while ((pos = line.find(delimiter)) != std::string::npos) {
				token = line.substr(0, pos);
				line.erase(0, pos + delimiter.length());
				if (i >= list.size()) break; //break from loop if this line has more cols than first line
				if (list[i] != NULL) Values[list[i]].push_back( (float) std::atof(token.c_str()) );
				i++;
			}
			//Grab last
			if (i >= list.size()) break; //break from loop if this line has more cols than first line
			if (list[i] != NULL) Values[list[i]].push_back( (float) std::atof(line.c_str()));
		}
	}
}
//returns true if all in memory recorded instants have been played back using PlayBack()
bool Macro::IsFinished() {
	return position >= length;
}
//returns a command that will play back all recorded instants (starting at 0) in memory then finish
Command* Macro::NewPlayCommand() {
	return new PlayBackCommand(this);
}
//Same as NewPlayCommand(), but on command run resets in memory recording this recording at file at FileName
Command* Macro::NewPlayFileCommand(std::string FileName) {
	return new PlayBackFileCommand(this,FileName);
}
//returns a command that will record a new instant from all sensors into memory until it is manually canceled
Command* Macro::NewRecordCommand() {
	return new RecordCommand(this);
}
//same as NewRecordCommand(), but writes in memory recording to file at FileName when command is finished
Command* Macro::NewRecordFileCommand(std::string FileName) {
	return new RecordFileCommand(this,FileName);
}
