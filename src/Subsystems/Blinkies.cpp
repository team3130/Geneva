#include "Blinkies.h"
#include "../RobotMap.h"

Blinkies* Blinkies::m_pInstance = NULL;

Blinkies::Blinkies() :	Subsystem("Blinkies")
{
	arduino = new SerialPort(57600, SerialPort::kMXP);
	arduino->SetWriteBufferMode(SerialPort::kFlushOnAccess);
}

void Blinkies::InitDefaultCommand()
{
}

Blinkies* Blinkies::GetInstance()
{
	if(!m_pInstance) m_pInstance = new Blinkies;
	return m_pInstance;
}

void Blinkies::PutCommand(std::string command, int param)
{
	Blinkies* my = GetInstance();
	std::ostringstream oss;
	oss << command;
	if (command.back() == '_') {
		oss << param;
	}
	oss << "\n";
	my->arduino->Write(oss.str(), oss.str().size());
}
