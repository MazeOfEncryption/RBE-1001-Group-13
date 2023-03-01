#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotor = motor(PORT10, ratio18_1, true);
motor rightMotor = motor(PORT1, ratio18_1, false);
line leftLineTracker = line(Brain.ThreeWirePort.C);
line rightLineTracker = line(Brain.ThreeWirePort.D);
/*vex-vision-config:begin*/
signature VisionSensor__RED_1 = signature (1, 7531, 9277, 8404, -551, -103, -327, 2.5, 0);
vision VisionSensor = vision (PORT2, 50, VisionSensor__RED_1);
/*vex-vision-config:end*/
motor liftMotor = motor(PORT8, ratio18_1, false);
motor intakeMotor = motor(PORT3, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}