#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotor = motor(PORT10, ratio18_1, false);
motor rightMotor = motor(PORT1, ratio18_1, true);
line leftLineTracker = line(Brain.ThreeWirePort.C);
line rightLineTracker = line(Brain.ThreeWirePort.D);
/*vex-vision-config:begin*/
signature VisionSensor__RED_1 = signature (1, 9513, 11145, 10330, -417, 1, -208, 4.8, 0);
signature VisionSensor__BLUE_1 = signature (2, -2509, -1855, -2182, 7681, 13145, 10414, 2.5, 0);
signature VisionSensor__YELLOW_1 = signature (3, 47, 909, 478, -3733, -3201, -3468, 2.5, 0);
vision VisionSensor = vision (PORT2, 50, VisionSensor__RED_1, VisionSensor__BLUE_1, VisionSensor__YELLOW_1);
/*vex-vision-config:end*/
motor liftMotor = motor(PORT8, ratio18_1, false);
motor intakeMotor = motor(PORT3, ratio18_1, false);
sonar rangeFinderBack = sonar(Brain.ThreeWirePort.A);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1RightShoulderControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // check the ButtonL1/ButtonL2 status to control intakeMotor
      if (Controller1.ButtonL1.pressing()) {
        intakeMotor.spin(forward);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonL2.pressing()) {
        intakeMotor.spin(reverse);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (!Controller1LeftShoulderControlMotorsStopped) {
        intakeMotor.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1LeftShoulderControlMotorsStopped = true;
      }
      // check the ButtonR1/ButtonR2 status to control liftMotor
      if (Controller1.ButtonR1.pressing()) {
        liftMotor.spin(forward);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonR2.pressing()) {
        liftMotor.spin(reverse);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (!Controller1RightShoulderControlMotorsStopped) {
        liftMotor.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}