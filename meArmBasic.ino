/* meArm IK test - York Hackspace May 2014
   Test applying Nick Moriarty's Inverse Kinematics solver
   to Phenoptix' meArm robot arm, to walk a specified path.

   Pins:
   Arduino    Base   Shoulder  Elbow    Gripper
*/
#include "meArm.h"
#include <Servo.h>

int basePin = 2;
int shoulderPin = 4;
int elbowPin = 3;
int gripperPin = 7;

meArm arm;

void setup() {
  arm.begin(basePin, shoulderPin, elbowPin, gripperPin);
  arm.gotoPointCylinder(0, 150, 25);

}

void loop() {

  arm.gotoPointCylinder(0,175,25);
  arm.gotoPointCylinder(-45,175,25);
  arm.gotoPointCylinder(0,175,25);
  arm.gotoPointCylinder(45,175,25);

  delay(1000);

}

