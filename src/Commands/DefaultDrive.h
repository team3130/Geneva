#ifndef DEFAULT_DRIVE_H
#define DEFAULT_DRIVE_H

#include <WPILib.h>
#include "Misc/ToggleClass.h"

/** Default command for driving the chassis.
 *
 * The default for the chassis is to be driven manually by a human operator.
 * This command reads the inputs from joysticks using the IO (operator interface) class
 * and controls the chassis via its public methods.
 */
class DefaultDrive: public Command
{
private:
	Toggle<bool>* shifterToggle;
	Toggle<bool>* driveModeToggle;
public:
	DefaultDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
