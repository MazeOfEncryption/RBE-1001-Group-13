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

const float wheelDiameter = 4.0f; // inches
const float wheelCircumference = 3.14 * wheelDiameter; // inches
const float gearRatio = 5.0f;
const float wheelTrack = 11.0f; // inches
const float speed = 70.0f; // RPM
const float lineFollowing_kP = 1.0f;
const float pctSpeed = 50;
const float motorCountPerRev = 900.0f;
const float countsPerInch = motorCountPerRev * gearRatio / wheelCircumference;

// Turn right until the robot has reached `targetDegrees` degrees
void turnRight (float targetDegrees) {
    // Calculate the number of degrees each motor must rotate for the entire robot to rotate `targetDegrees` degrees.
    float rotationDegrees = targetDegrees * gearRatio * wheelTrack / wheelDiameter;
    // Non-blocking so that rightMotor.spinFor() can happen simultaneously
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

// Follows a line until the range finder is within `stopDistance` of a wall
void followLine (float stopDistance) {
    // Reset encoder counts on left and right motors
    leftMotor.resetRotation();
    rightMotor.resetPosition();
    // Follow the line using proportional control until the range finder is within `stopDistance` inches of the wall
    while (rangeFinder.distance(distanceUnits::in) > stopDistance) {
        float error = leftLineTracker.reflectivity() - rightLineTracker.reflectivity();
        drive(speed, error * lineFollowing_kP);
    }
    // Stop both motors after line following is complete
    leftMotor.stop(brake);
    rightMotor.stop(brake);
}

int main() {
    vexcodeInit(); // Initializing Robot Configuration. DO NOT REMOVE!
    vexDelay(500); // Wait for range finder to initialize - the value will be 0 initially

    followLine(9.3); // Stop when 9.3 inches away from the wall
    turnRight(-92); // 92 degrees instead of 90 to account for underturning 
    followLine(2.0); // Stop when 2.0 inches away from the wall
    turnRight(-92); // 92 degrees instead of 90 to account for underturning 
    followLine(9.3); // Stop when 9.3 inches away from the wall
}
