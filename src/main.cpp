// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor            motor         1               
// rightMotor           motor         2               
// leftLineTracker      line          G               
// rightLineTracker     line          H               
// VisionSensor         vision        20              
// liftMotor            motor         8               
// intakeMotor          motor         3               
// rangeFinderBack      sonar         E, F            
// Controller1          controller                    
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
const float intakeDriveSpeed = 130.0f; // RPM
const float degreesPerInch = 360.0f / wheelCircumference;
// const float motorCountPerRev = 900.0f;
// const float countsPerInch = motorCountPerRev * gearRatio / wheelCircumference;

// Function to drive forwards `distance` inches.
void driveStraight (float distance, float speed = pctSpeed) {
    // leftMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, false);
    // rightMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, true);
    leftMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, speed, velocityUnits::pct, false);
    rightMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, speed, velocityUnits::pct, true);
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
    leftMotor.setVelocity(speed + direction, rpm);
    rightMotor.setVelocity(speed - direction, rpm);
    leftMotor.spin(fwd);
    rightMotor.spin(fwd);
}

// If rangeFinder is false: follow a line for `dist` inches
// If rangeFinder is true: follow a line until the rangefinder is within `stopDist` inches of the wall
void followLine (float dist, bool rangeFinder = false) {
    // Reset encoder counts on left and right motors
    leftMotor.resetRotation();
    rightMotor.resetPosition();
    bool stopCondition = false;
    while (!stopCondition) {
        if (rangeFinder) {
            stopCondition = rangeFinderBack.distance(distanceUnits::in) < dist;
            std::cout << "Distance: " << rangeFinderBack.distance(distanceUnits::in) << std::endl;
        } else {
            stopCondition = leftMotor.position(rev) / gearRatio * wheelCircumference > dist;
        }
        float error = leftLineTracker.reflectivity() - rightLineTracker.reflectivity();
        drive(speed, error * lineFollowing_kP);
    }
    // Stop both motors after line following is complete
    leftMotor.stop(brake);
    rightMotor.stop(brake);
}

void armUp (bool waitForCompletion = true) {
    liftMotor.spinFor(forward, 0.75f, rotationUnits::rev, 25, velocityUnits::pct, waitForCompletion);
}
void armDown(bool waitForCompletion = true) {
    liftMotor.spinFor(reverse, 0.75f, rotationUnits::rev, 25, velocityUnits::pct, waitForCompletion);
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
    std::cout << "x: " << VisionSensor.largestObject.centerX;
    std::cout << " y: " << VisionSensor.largestObject.centerY;
    std::cout << " width: " << VisionSensor.largestObject.width << std::endl;
    // Brain.Screen.print("Distance: %f", distanceToBall(VisionSensor.largestObject.centerY));
    // std::cout << VisionSensor.objectCount << std::endl;
    if (VisionSensor.objectCount > 0) {
        // Return false if ball is out of range (too close or too far away from the vision sensor)
        // if (VisionSensor.largestObject.centerY < 135 || VisionSensor.largestObject.centerY > 200) return false;
        return true;
    } else return false;
}

// Uses the vision sensor to line the robot up and approach a ball
void approachBall (signature &sig) {
    while (DetectObject(sig)) {
        float error_distance = centerX - VisionSensor.largestObject.centerX;
        drive(-intakeDriveSpeed, error_distance *  kP_angle);
        vexDelay(30);
    }
    leftMotor.stop(brake);
    rightMotor.stop(brake);
}
// Drives the robot towards the ball and intakes it
void intakeBall () {
    driveStraight(-1);
    // It's important that the intake mechanism turns the same amount for each ball,
    // so that the intake paddles are lined up properly
    intakeMotor.spinFor(1.0f, rotationUnits::rev, 50, velocityUnits::pct, false);
    driveStraight(-2);
}
int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    vexDelay(500); // wait half a second for ultrasonic sensor to initialize

    approachBall(VisionSensor__RED_1);
    intakeBall();
    turn(90);
    approachBall(VisionSensor__BLUE_1);
    intakeBall();
    turn(-25);
    approachBall(VisionSensor__RED_1);
    intakeBall();
    intakeMotor.spin(forward);
    vexDelay(500);
    intakeMotor.stop(brake);

    driveStraight(16);
    turn(130);
    driveStraight(6);

    followLine(3.5, true); // Approach the V-Bucket
    armUp(); // Hook onto it
    driveStraight(-8); // Back up to collect yellow ball
    armDown(); // Put arm back down
    followLine(4.5, true); // Approach the V-Bucket again
    armUp(); // Hook onto it
    intakeMotor.spinFor(5.0f, rotationUnits::rev, 25, velocityUnits::pct, true);
    armDown();
    driveStraight(-4);
    // armUp();
    // Make sure arm is ALL THE WAY up
    liftMotor.spinFor(forward, 0.85f, rotationUnits::rev, 25, velocityUnits::pct, true);
    // this is horrible but it works
    driveStraight(8, 100);
    driveStraight(-6, 100);
    driveStraight(8, 100);
    driveStraight(-12, 100);
    turn(-180);
    
    followLine(9.3, true);
    turn(-90);
    followLine(38);
    turn(-105);
    followLine(60);
}