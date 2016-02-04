#ifndef CONTROL_INTAKE_WHEELS_H
#define CONTROL_INTAKE_WHEELS_H

#include <WPILib.h>
#include "Misc/ToggleClass.h"

/** Default command for driving the chassis.
 *
 * The default for the chassis is to be driven manually by a human operator.
 * This command reads the inputs from joysticks using the IO (operator interface) class
 * and controls the chassis via its public methods.
 */
class ControlIntakeWheels: public Command
{
private:
	Toggle<bool>* IntakeArmPosition;
public:
	ControlIntakeWheels();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
