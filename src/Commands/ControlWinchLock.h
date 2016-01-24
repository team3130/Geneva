#ifndef CONTROL_INTAKE_H
#define CONTROL_INTKAE_H

#include <WPILib.h>
#include "Misc/ToggleClass.h"

/** Default command for driving the chassis.
 *
 * The default for the chassis is to be driven manually by a human operator.
 * This command reads the inputs from joysticks using the IO (operator interface) class
 * and controls the chassis via its public methods.
 */
class ControlWinchLockCommand: public Command
{
public:
	ControlWinchLockCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
