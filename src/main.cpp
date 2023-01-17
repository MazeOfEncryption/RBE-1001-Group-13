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
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

const float wheelDiameter = 4.0f;
const float wheelCircumference = 3.14 * wheelDiameter;
const float gearRatio = 5.0f;
const float wheelTrack = 11.0f;
const float degreesPerInch = 360.0f / wheelCircumference;

void driveStraight (float inches) {
    
    leftMotor.spinFor(forward, gearRatio * inches * degreesPerInch, degrees, false);
    rightMotor.spinFor(forward, gearRatio * inches * degreesPerInch, degrees, true);
}

void turnRight (float targetDegrees) {
    float rotationDegrees = targetDegrees * gearRatio * wheelTrack / wheelDiameter;
    leftMotor.spinFor(forward, rotationDegrees, degrees, false);
    rightMotor.spinFor(reverse, rotationDegrees, degrees, true);
}
void polygon (int sides, float sideLength) {
    for (int i = 0; i < sides; i++) {
        driveStraight(sideLength);
        turnRight(360.0f / sides + 2.0f);
    }
}

int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    // Brain.Screen.print("Hello, world!");
    // driveStraight(10);
    
    // turnRight(90);
    polygon(5, 7.87402f);
}
