#ifndef ReloadCatapult_H
#define ReloadCatapult_H

#include "WPILib.h"

class ReloadCatapult: public Command
{
private:
	uint32_t m_button;
	bool m_buttonHold;
	bool m_goingUp;
	Timer m_timer;
public:
	ReloadCatapult(uint32_t button_number);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
