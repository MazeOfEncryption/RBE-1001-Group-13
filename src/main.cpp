// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor            motor         10              
// rightMotor           motor         1               
// leftLineTracker      line          C               
// rightLineTracker     line          D               
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
const float degreesPerInch = 360.0f / wheelCircumference;
const float speed = 70.0f; // RPM
const float lineFollowing_kP = 1.0f;
// const float pctSpeed = 50;
// const float motorCountPerRev = 900.0f;
// const float countsPerInch = motorCountPerRev * gearRatio / wheelCircumference;
// const float baseVoltage = 6.0f;
// const float distanceInches = 11.0f;
// const float setDistance = 11.0f; // inches
// // const float kP = 10.0f;
// const float setWallFollowSpeed = 70.0f; // RPM
// const float setWallDistance = 11.0f; // inches for wall following
// const float turnAngleAtWall = 90.0f; // turn left angle in degrees
// const float setDistToStartTurn = 8.0f; // Inches from walll in front to begin turn


// Turn right until the robot has reached `targetDegrees` degrees
void turnRight (float targetDegrees) {
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

void drive(float speed, float direction) {
    leftMotor.setVelocity(speed - direction, rpm);
    rightMotor.setVelocity(speed + direction, rpm);
    leftMotor.spin(fwd);
    rightMotor.spin(fwd);
}

void followLine (float distance) {
    // Distance is in inches
    // TODO use ultrasonic sensor for stop condition
    int distanceRaw = (int)(countsPerInch * distance);
    leftMotor.resetRotation();
    rightMotor.resetPosition();
    while (leftMotor.rotation(rotationUnits::raw) < distanceRaw) {
        float error = leftLineTracker.reflectivity() - rightLineTracker.reflectivity();
        drive(speed, error * lineFollowing_kP);
    }
    leftMotor.stop(brake);
    rightMotor.stop(brake);
}

int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    followLine(20); // temporary - later, use ultrasonic sensor for stop condition
}
