// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor            motor         10              
// rightMotor           motor         1               
// leftLineTracker      line          C               
// rightLineTracker     line          D               
// VisionSensor         vision        2               
// liftMotor            motor         8               
// intakeMotor          motor         3               
// rangeFinderBack      sonar         A, B            
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
#include <iostream>

using namespace vex;

const float resolutionX = 316; // Pixels
const float resolutionY = 212; // Pixels
const int centerX = 157; // Pixels
const int centerY = 105; // Pixels

const float wheelDiameter = 4.0f; // inches
const float wheelCircumference = 3.14 * wheelDiameter; // inches
const float gearRatio = 5.0f;
const float wheelTrack = 11.0f; // inches
const float speed = 120.0f; // RPM
const float lineFollowing_kP = 1.0f;
const float kP_angle = 1.0f;
const float pctSpeed = 50.0f;
const float intakeDriveSpeed = 70.0f; // RPM
const float degreesPerInch = 360.0f / wheelCircumference;
// const float motorCountPerRev = 900.0f;
// const float countsPerInch = motorCountPerRev * gearRatio / wheelCircumference;

// Function to drive forwards `distance` inches.
void driveStraight (float distance) {
    // leftMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, false);
    // rightMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, true);
    leftMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, pctSpeed, velocityUnits::pct, false);
    rightMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, pctSpeed, velocityUnits::pct, true);
}

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

// Returns true if RED_BALL is detected and false if not,
// and prints debug information to the screen on the brain
bool DetectObject(signature &sig) {
    VisionSensor.takeSnapshot(sig);
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("x: %d ", VisionSensor.largestObject.centerX);
    Brain.Screen.print("y: %d ", VisionSensor.largestObject.centerY);
    Brain.Screen.print("Width: %d ", VisionSensor.largestObject.width);
    // Brain.Screen.print("Distance: %f", distanceToBall(VisionSensor.largestObject.centerY));
    // std::cout << VisionSensor.objectCount << std::endl;
    if (VisionSensor.objectCount > 0) {
        // Return false if ball is out of range (too close or too far away from the vision sensor)
        // if (VisionSensor.largestObject.centerY < 135 || VisionSensor.largestObject.centerY > 200) return false;
        return true;
    } else return false;
}

// This is horrible. Do not read it. All that you need to know is that it works.
void collectBall (signature &sig) {
    int counter = 0;
    while (counter++ < 50) {
        if (DetectObject(sig)) counter = 0;
        std::cout << "Counter: " << counter << " centerX: " << VisionSensor.largestObject.centerX << std::endl;
        float error_distance = centerX - VisionSensor.largestObject.centerX;
        if (VisionSensor.objectCount > 0) {
            drive(-intakeDriveSpeed, error_distance *  kP_angle);
        } else {
            drive(-intakeDriveSpeed, 0);    
        }
        intakeMotor.spin(forward, 100, velocityUnits::pct);
        vexDelay(30);
    }
    leftMotor.stop(brake);
    rightMotor.stop(brake);
    intakeMotor.stop(brake);
}
int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    vexDelay(500); // wait half a second for ultrasonic sensor to initialize

    // armUp();
    collectBall(VisionSensor__RED_1);
    // vexDelay(1000);
    // armDown();
    // vexDelay(1000);
    // driveStraight(-4);

    // followLine(48.0f);
    // liftMotor.rotateFor(1, rotationUnits::rev, );   
}