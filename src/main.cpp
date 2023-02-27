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
const float speed = 70.0f; // RPM
const float lineFollowing_kP = 1.0f;
const float pctSpeed = 50;
const float motorCountPerRev = 900.0f;
const float countsPerInch = motorCountPerRev * gearRatio / wheelCircumference;

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

// Function to drive forwards `distance` inches.
void driveStraight (float distance) {
    // leftMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, false);
    // rightMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, true);
    leftMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, pctSpeed, velocityUnits::pct, false);
    rightMotor.spinFor(forward, gearRatio * distance * degreesPerInch, degrees, pctSpeed, velocityUnits::pct, true);
}
// void driveForwards(float speed, float distance) {
//     float kP = 1.0f;
//     int distanceRaw = (int)(countsPerInch * distance);
//     leftMotor.resetRotation();
//     rightMotor.resetPosition();
//     while (leftMotor.rotation(rotationUnits::raw) < distanceRaw) {
//         float error = (leftMotor.rotation(rotationUnits::raw) - rightMotor.rotation(rotationUnits::raw));
//         leftMotor.spin(forward, baseVoltage - kP * error, volt);
//         leftMotor.spin(forward, baseVoltage + kP * error, volt);
//     }
//     leftMotor.stop(brake);
//     rightMotor.stop(brake);
// }

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

// // Drive in a polygon with `sides` sides and `sideLegnth` side lengths, mesured in inches
// void polygon (int sides, float sideLength) {
//     // Repeat for each side of the polygon
//     for (int i = 0; i < sides; i++) {
//         // Drive forwards for `sideLength` inches
//         driveStraight(sideLength);
//         // Add a 2 degree "fudge factor" to account for the robot not turning enough.
//         // (This could be due to friciton in the drivetrain, wheel slippage, etc.)
//         turnRight(360.0f / sides + 2.0f);
//     }
// }


// void drive(float speed, float direction) {
//     leftMotor.setVelocity(speed - direction, rpm);
//     rightMotor.setVelocity(speed + direction, rpm);
//     leftMotor.spin(fwd);
//     rightMotor.spin(fwd);
// }

// void wallFollowInches(float setDistanceFromWall) {
//     float error = /* ? */;
//     drive(setWallFollowSpeed, kP * error);
// }

int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    // Draw a pentagon with 5 sides and 20cm (7.87402 inch) side lengths
    // polygon(5, 7.87402f);
    driveStraight(43.5);
    turnRight(-92);
    driveStraight(79);
    turnRight(-92);
    driveStraight(33.5);

    // float kP = 10.0f;
    // for(;;) {
    //     float error = rangeFinderFront.distance(inches) - setDistance;
    //     Brain.Screen.printAt(30, 30, "%f         \n", error);
    //     printf("Error = %g\n", error);
    //     leftMotor.setVelocity(kP * error, rpm);
    //     rightMotor.setVelocity(kP * error, rpm);
    //     leftMotor.spin(fwd);
    //     rightMotor.spin(fwd);
    // }
}
