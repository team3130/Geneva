/*
 * PlayBackCommand.h
 *
 *  Created on: Apr 5, 2015
 *      Author: kma1660
 */

#ifndef SRC_RIPTIDERECORDER_PLAYBACKCOMMAND_H_
#define SRC_RIPTIDERECORDER_PLAYBACKCOMMAND_H_

#include "WPILib.h"
#include <string>
#include "../Macro.h"

class PlayBackCommand : public Command{
public:
	PlayBackCommand(Macro* m);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
protected:
	Macro* macro;
};

#endif /* SRC_RIPTIDERECORDER_PLAYBACKCOMMAND_H_ */
