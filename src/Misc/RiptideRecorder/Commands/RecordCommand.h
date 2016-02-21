/*
 * RecordCommand.h
 *
 *  Created on: Apr 5, 2015
 *      Author: kma1660
 */

#ifndef SRC_RIPTIDERECORDER_RECORDCOMMAND_H_
#define SRC_RIPTIDERECORDER_RECORDCOMMAND_H_

#include "WPILib.h"
#include "../Macro.h"

class RecordCommand : public Command{
	public:
		RecordCommand(Macro* m);
		virtual void Initialize();
		virtual void Execute();
		virtual bool IsFinished();
		virtual void End();
		virtual void Interrupted();
	protected:
		Macro* macro;
};

#endif /* SRC_RIPTIDERECORDER_RECORDCOMMAND_H_ */
