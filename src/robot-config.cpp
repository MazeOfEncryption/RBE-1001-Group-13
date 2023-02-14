#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotor = motor(PORT10, ratio18_1, true);
motor rightMotor = motor(PORT1, ratio18_1, false);
/*vex-vision-config:begin*/
signature VisionSensor__RED_BALL = signature (1, 11013, 13187, 12100, -1549, -851, -1200, 4.6, 0);
signature VisionSensor__BLUE_BALL = signature (2, -2357, -1731, -2044, 10313, 12637, 11475, 2.5, 0);
signature VisionSensor__YELLOW_BALL = signature (3, 253, 771, 512, -3501, -2875, -3188, 2.5, 0);
vision VisionSensor = vision (PORT7, 50, VisionSensor__RED_BALL, VisionSensor__BLUE_BALL, VisionSensor__YELLOW_BALL);
/*vex-vision-config:end*/
sonar rangeFinder = sonar(Brain.ThreeWirePort.A);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}