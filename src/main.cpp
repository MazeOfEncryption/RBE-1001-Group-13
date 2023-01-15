/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Maze                                             */
/*    Created:      Thu Jan 12 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

const float wheelDiameter = 4.0f;
const float wheelCircumference = 3.14 * wheelDiameter;
const float gearRatio = 5.0f;
const float wheelTrack = 11.0f;

void driveStraight (float inches) {
    leftMotor.spinFor(forward, gearRatio * inches * degreesPerInch, degrees, false);
    rightMotor.spinFor(forward, gearRatio * inches * degreesPerInch, degrees, true);
}

void turnRight (float targetDegrees) {
    float rotationDegrees = targetDegrees * gearRatio * wheelTrack / wheelDiameter;
    leftMotor.spinFor(forward, rotationDegrees, degress, false);
    rightMotor.spinFor(reverse, rotationDegrees, degrees, true);
}

int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    // Brain.Screen.print("Hello, world!");
    driveStraight(10);
    turnRight(90);
}
