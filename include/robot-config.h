using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor leftMotor;
extern motor rightMotor;
extern line leftLineTracker;
extern line rightLineTracker;
extern signature VisionSensor__RED_1;
extern signature VisionSensor__SIG_2;
extern signature VisionSensor__SIG_3;
extern signature VisionSensor__SIG_4;
extern signature VisionSensor__SIG_5;
extern signature VisionSensor__SIG_6;
extern signature VisionSensor__SIG_7;
extern vision VisionSensor;
extern motor liftMotor;
extern motor intakeMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );