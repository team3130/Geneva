#ifndef AUTON_FIRE_H
#define AUTON_FIRE_H

#include <WPILib.h>

/** Default command for driving the chassis.
 *
 * The default for the chassis is to be driven manually by a human operator.
 * This command reads the inputs from joysticks using the IO (operator interface) class
 * and controls the chassis via its public methods.
 */
class AutonFire: public Command
{
private:
	Timer* timer;
	bool m_waiting;

	float m_timeout;
public:
	AutonFire();
	~AutonFire();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void SetParam(float timeout){
		m_timeout = timeout;
	}
};

#endif
