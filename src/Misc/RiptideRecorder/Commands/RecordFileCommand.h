/*
 * RecordFileCommand.h
 *
 *  Created on: Oct 7, 2015
 *      Author: michael
 */

#ifndef SRC_RIPTIDERECORDER_COMMANDS_RECORDFILECOMMAND_H_
#define SRC_RIPTIDERECORDER_COMMANDS_RECORDFILECOMMAND_H_

#include "RecordCommand.h"

class RecordFileCommand : public RecordCommand {
public:
	RecordFileCommand(Macro* m,std::string f);
	void End();
private:
	std::string filename;
};

#endif /* SRC_RIPTIDERECORDER_COMMANDS_RECORDFILECOMMAND_H_ */
