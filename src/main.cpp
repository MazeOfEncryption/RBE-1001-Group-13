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

const float wheelDiameter = 4.0f; // inches
const float wheelCircumference = 3.14 * wheelDiameter; // inches 
const float gearRatio = 5.0f;
const float wheelTrack = 11.0f; // inches
const float degreesPerInch = 360.0f / wheelCircumference;
const float pctSpeed = 50; // 50 percent speed

// Function to drive forwards `distance` inches.
void driveStraight (float distance) {
    leftMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, pctSpeed, velocityUnits::pct, false);
    rightMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, pctSpeed, velocityUnits::pct, true);
}

// Turn right until the robot has reached `targetDegrees` degrees
void turnRight (float targetDegrees) {
    // Calculate the number of degrees each motor must rotate for the entire robot to rotate `targetDegrees` degrees.
    float rotationDegrees = targetDegrees * gearRatio * wheelTrack / wheelDiameter;

    leftMotor.spinFor(forward, rotationDegrees, degrees, pctSpeed, velocityUnits::pct, false);
    rightMotor.spinFor(reverse, rotationDegrees, degrees, pctSpeed, velocityUnits::pct, true);
}

int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    driveStraight(43.5);
    turnRight(-92); // 92 instead of 90 to account for underrotation
    driveStraight(79);
    turnRight(-92); // 92 instead of 90 to account for underrotation
    driveStraight(33.5);
}
