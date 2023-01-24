/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Maze                                             */
/*    Created:      Thu Jan 12 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor            motor         10              
// rightMotor           motor         1               
// leftLineTracker      line          C               
// rightLineTracker     line          D               
// rangeFinder          sonar         A, B            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
    while(true) {
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1);
        Brain.Screen.print("Left: %d  ", leftLineTracker.reflectivity());
        Brain.Screen.print("Right: %d  ", rightLineTracker.reflectivity());
        Brain.Screen.print("Distance: %f", rangeFinder.distance(distanceUnits::in));
        vexDelay(50);
    }
}