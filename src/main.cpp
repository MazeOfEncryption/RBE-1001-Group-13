// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor            motor         10              
// rightMotor           motor         1               
// leftLineTracker      line          C               
// rightLineTracker     line          D               
// VisionSensor         vision        2               
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Maze                                             */
/*    Created:      Thu Jan 12 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

const float wheelDiameter = 4.0f; // inches
const float wheelCircumference = 3.14 * wheelDiameter; // inches
const float gearRatio = 5.0f;
const float wheelTrack = 11.0f; // inches
const float speed = 70.0f; // RPM
const float lineFollowing_kP = 1.0f;
const float pctSpeed = 50;
// const float motorCountPerRev = 900.0f;
// const float countsPerInch = motorCountPerRev * gearRatio / wheelCircumference;

// // Function to drive forwards `distance` inches.
// void driveStraight (float distance) {
//     // leftMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, false);
//     // rightMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, true);
//     leftMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, pctSpeed, velocityUnits::pct, false);
//     rightMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, pctSpeed, velocityUnits::pct, true);
// }

// Turn until the robot has reached `targetDegrees` degrees.
// Positive = right, negative = left
void turn (float targetDegrees) {
    // Calculate the number of degrees each motor must rotate for the entire robot to rotate `targetDegrees` degrees.
    float rotationDegrees = targetDegrees * gearRatio * wheelTrack / wheelDiameter;
    // Non-blocking so that rightMotor.spinFor() can happen simultaneously
    // leftMotor.spinFor(forward, rotationDegrees, degrees, false);
    // rightMotor.spinFor(reverse, rotationDegrees, degrees, true);
    // leftMotor.resetPosition();
    // leftmotor.spinTo();
    leftMotor.spinFor(forward, rotationDegrees, degrees, pctSpeed, velocityUnits::pct, false);
    rightMotor.spinFor(reverse, rotationDegrees, degrees, pctSpeed, velocityUnits::pct, true);
}

// Drive forwards with a direction. A positive direction means steering left, and a negative direction means steering right
void drive(float speed, float direction) {
    leftMotor.setVelocity(speed - direction, rpm);
    rightMotor.setVelocity(speed + direction, rpm);
    leftMotor.spin(fwd);
    rightMotor.spin(fwd);
}

// Follows a line for `dist` inches
void followLine (float dist) {
    // Reset encoder counts on left and right motors
    leftMotor.resetRotation();
    rightMotor.resetPosition();
    // Follow the line using proportional control until the range finder is within `stopDistance` inches of the wall
    // while (rangeFinder.distance(distanceUnits::in) > stopDistance) {
    while (leftMotor.position(rev) / gearRatio * wheelCircumference < dist) {
        float error = leftLineTracker.reflectivity() - rightLineTracker.reflectivity();
        drive(speed, error * lineFollowing_kP);
    }
    // Stop both motors after line following is complete
    leftMotor.stop(brake);
    rightMotor.stop(brake);
}

void armUp (bool waitForCompletion = true) {
    liftMotor.spinFor(forward, 0.8f, rotationUnits::rev, 25, velocityUnits::pct, waitForCompletion);
}
void armDown(bool waitForCompletion = true) {
    liftMotor.spinFor(reverse, 0.8f, rotationUnits::rev, 25, velocityUnits::pct, waitForCompletion);
}

int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    armUp();
    vexDelay(1000);
    armDown();

    // followLine(12.0f);
    // liftMotor.rotateFor(1, rotationUnits::rev, );
    
}
