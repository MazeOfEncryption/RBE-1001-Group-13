// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor            motor         10              
// rightMotor           motor         1               
// VisionSensor         vision        7               
// rangeFinder          sonar         A, B            
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

const float pi = 3.14159265359;

const float kP_angle = 1.0f;
const float kP_distance = 10.0f;

const float resolutionX = 316; // Pixels
const float resolutionY = 212; // Pixels
const int centerX = 157; // Pixels
const int centerY = 105; // Pixels

const float followDistance = 10.0f; // inches

const float ballRadius = 1; // inche
const float cameraHeight = 2.75; // inches
const float horizontalFOV = 47; // degrees
const float degreesPerPixelY = horizontalFOV / resolutionY;

float distanceToBall(float height) {
    return (ballRadius - cameraHeight) / atan(degreesPerPixelY * (height - centerY) * pi / 180.0f);
}

// Returns true if RED_BALL is detected and false if not,
// and prints debug information to the screen on the brain
bool DetectObject() {
    VisionSensor.takeSnapshot(VisionSensor__RED_BALL);
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("x: %d ", VisionSensor.largestObject.centerX);
    Brain.Screen.print("y: %d ", VisionSensor.largestObject.centerY);
    Brain.Screen.print("Width: %d ", VisionSensor.largestObject.width);
    Brain.Screen.print("Distance: %f", distanceToBall(VisionSensor.largestObject.centerY));
    if (VisionSensor.objectCount > 0) {
        return true;
    } else return false;
}

// Drive forwards with a direction. A positive direction means steering left,
// and a negative direction means steering right
void drive(float speed, float direction) {
    leftMotor.setVelocity(speed - direction, rpm);
    rightMotor.setVelocity(speed + direction, rpm);
    leftMotor.spin(fwd);
    rightMotor.spin(fwd);
}

int main() {
    vexcodeInit();
    vexDelay(500); // wait half a second for ultrasonic sensor to initialize
    while (true) {
        // Only drive if a ball is detected
        if (DetectObject()) {
            float error_angle = centerX - VisionSensor.largestObject.centerX;
            float distance = rangeFinder.distance(distanceUnits::in);
            float error_distance = distance - followDistance;
            // drive(0, error_angle * kP_angle); // angle only
            // drive(error_distance * kP_distance, 0); // distance only
            // drive(error_distance * kP_distance, error_angle * kP_angle); // both angle and distance
        } else {
            // If no ball is detected, stop motors.
            leftMotor.stop(brake);
            rightMotor.stop(brake);
        }
        vexDelay(30);
    }
}
