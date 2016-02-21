#include <string.h>
#include "ReadRecord.h"
#include "Misc/RiptideRecorder/RiptideRecorder.h"


ReadRecord::ReadRecord()
	:m_timeout(0)
	,m_readFile("")
{
	timer = new Timer();
	readMacro = Recorder::GetInstance()->macro();
}

ReadRecord::~ReadRecord()
{
	delete timer;
}

// Called just before this Command runs the first time
void ReadRecord::Initialize()
{
	readMacro->ReadFile("/AutonCommands/RecordFiles/" + m_readFile);
	readMacro->PlayReset();
}

// Called repeatedly when this Command is scheduled to run
void ReadRecord::Execute()
{
	if(!readMacro->IsFinished()) readMacro->PlayBack();
}

// Make this return true when this Command no longer needs to run execute()
bool ReadRecord::IsFinished()
{
	if(m_timeout > 0){
		if(timer->Get() > m_timeout) return true;
	}
	return readMacro->IsFinished();
}

// Called once after isFinished returns true
void ReadRecord::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReadRecord::Interrupted()
{

}
