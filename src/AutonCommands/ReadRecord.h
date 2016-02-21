#ifndef READ_RECORD_H
#define READ_RECORD_H

#include <WPILib.h>
#include <string.h>
#include "Misc/RiptideRecorder/RiptideRecorder.h"

class ReadRecord: public Command
{
private:
	Macro* readMacro;
	Timer* timer;

	float m_timeout;
	std::string m_readFile;
public:
	ReadRecord();
	~ReadRecord();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetParam(float timeout, char readFile){
		m_timeout = timeout;
		m_readFile = readFile;
	}
};

#endif
