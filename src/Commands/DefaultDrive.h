#ifndef DEFAULT_DRIVE_H
#define DEFAULT_DRIVE_H

#include <WPILib.h>

/** Default command for driving the chassis.
 *
 * The default for the chassis is to be driven manually by a human operator.
 * This command reads the inputs from joysticks using the IO (operator interface) class
 * and controls the chassis via its public methods.
 */
class DefaultDriveCommand: public Command
{
public:
	DefaultDriveCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
