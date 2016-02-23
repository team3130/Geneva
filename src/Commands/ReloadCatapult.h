#ifndef RELOAD_CATAPULT_H
#define RELOAD_CATAPULT_H

#include <WPILib.h>

class ReloadCatapult: public Command
{
	static constexpr char STR_PRESET[] = "WinchPositionA";
private:
	char m_presetLabel[sizeof(STR_PRESET)];
	uint32_t m_button;
	bool m_buttonHold;
	bool m_goingUp;
	Timer m_timer;
public:
	ReloadCatapult(uint32_t button_number, bool remote = false);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
