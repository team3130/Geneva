/*
 * PlayBackFileCommand.cpp
 *
 *  Created on: Oct 7, 2015
 *      Author: michael
 */

#include "PlayBackFileCommand.h"

PlayBackFileCommand::PlayBackFileCommand(Macro* m, std::string f) : PlayBackCommand(m) {
	this->filename = f;
}
void PlayBackFileCommand::Initialize() {
	macro->ReadFile(filename);
	macro->PlayReset();
}

