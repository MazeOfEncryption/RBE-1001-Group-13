#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotor = motor(PORT1, ratio18_1, false);
motor rightMotor = motor(PORT2, ratio18_1, true);
line leftLineTracker = line(Brain.ThreeWirePort.G);
line rightLineTracker = line(Brain.ThreeWirePort.H);
/*vex-vision-config:begin*/
signature VisionSensor__RED_1 = signature (1, 8151, 10027, 9088, -289, 149, -70, 6.1, 0);
signature VisionSensor__BLUE_1 = signature (2, -2509, -1855, -2182, 7681, 13145, 10414, 2.5, 0);
signature VisionSensor__YELLOW_1 = signature (3, 47, 909, 478, -3733, -3201, -3468, 2.5, 0);
vision VisionSensor = vision (PORT20, 50, VisionSensor__RED_1, VisionSensor__BLUE_1, VisionSensor__YELLOW_1);
/*vex-vision-config:end*/
motor liftMotor = motor(PORT8, ratio18_1, false);
motor intakeMotor = motor(PORT3, ratio18_1, false);
sonar rangeFinderBack = sonar(Brain.ThreeWirePort.E);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1UpDownButtonsControlMotorsStopped = true;
bool Controller1XBButtonsControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // check the ButtonUp/ButtonDown status to control liftMotor
      if (Controller1.ButtonUp.pressing()) {
        liftMotor.spin(forward);
        Controller1UpDownButtonsControlMotorsStopped = false;
      } else if (Controller1.ButtonDown.pressing()) {
        liftMotor.spin(reverse);
        Controller1UpDownButtonsControlMotorsStopped = false;
      } else if (!Controller1UpDownButtonsControlMotorsStopped) {
        liftMotor.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1UpDownButtonsControlMotorsStopped = true;
      }
      // check the ButtonX/ButtonB status to control intakeMotor
      if (Controller1.ButtonX.pressing()) {
        intakeMotor.spin(forward);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (Controller1.ButtonB.pressing()) {
        intakeMotor.spin(reverse);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (!Controller1XBButtonsControlMotorsStopped) {
        intakeMotor.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1XBButtonsControlMotorsStopped = true;
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