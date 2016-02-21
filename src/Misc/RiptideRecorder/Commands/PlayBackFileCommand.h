/*
 * PlayBackFileCommand.h
 *
 *  Created on: Oct 7, 2015
 *      Author: michael
 */

#ifndef SRC_RIPTIDERECORDER_COMMANDS_PLAYBACKFILECOMMAND_H_
#define SRC_RIPTIDERECORDER_COMMANDS_PLAYBACKFILECOMMAND_H_

#include "../Macro.h"
#include "PlayBackCommand.h"

class PlayBackFileCommand : public PlayBackCommand {
public:
	PlayBackFileCommand(Macro* m, std::string f);
	void Initialize();
private:
	std::string filename;
};

#endif /* SRC_RIPTIDERECORDER_COMMANDS_PLAYBACKFILECOMMAND_H_ */
