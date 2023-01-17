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

// Function to drive forwards `distance` inches.
void driveStraight (float distance) {
    leftMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, false);
    rightMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, true);
}

// Turn right until the robot has reached `targetDegrees` degrees
void turnRight (float targetDegrees) {
    // Calculate the number of degrees each motor must rotate for the entire robot to rotate `targetDegrees` degrees.
    float rotationDegrees = targetDegrees * gearRatio * wheelTrack / wheelDiameter;
    // Non-blocking so that rightMotor.spinFor() can happen simultaneously
    leftMotor.spinFor(forward, rotationDegrees, degrees, false);
    rightMotor.spinFor(reverse, rotationDegrees, degrees, true);
}

// Drive in a polygon with `sides` sides and `sideLegnth` side lengths, mesured in inches
void polygon (int sides, float sideLength) {
    // Repeat for each side of the polygon
    for (int i = 0; i < sides; i++) {
        // Drive forwards for `sideLength` inches
        driveStraight(sideLength);
        // Add a 2 degree "fudge factor" to account for the robot not turning enough.
        // (This could be due to friciton in the drivetrain, wheel slippage, etc.)
        turnRight(360.0f / sides + 2.0f);
    }
}

int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    // Draw a pentagon with 5 sides and 20cm (7.87402 inch) side lengths
    polygon(5, 7.87402f);
}
