/*
   Test applying Nick Moriarty's Inverse Kinematics solver
   to Phenoptix' meArm robot arm.

   The Controller is an S4A Edu robotic controller board

   Send x,y,z,g Cylindrical coordinates over Serial port
   x = -1.0 a 1.0
   y = mm
   z = mm
   g = gripper OPEN 0, CLOSE 1
   
   Example: 0,150,50,0 (home position with gripper open)
   
   Analog Joysticks connected to pins A0-A3
*/
#include "meArm.h"
#include <Servo.h>

int basePin = 2;
int shoulderPin = 3;
int elbowPin = 4;
int gripperPin = 7;

String inputString = "";
String xString = "";
String yString = "";
String zString = "";
String gString = "";
boolean stringComplete = false;
float x = 0.00;
float y = 150.00;
float z = 50.00;

meArm arm;

void setup() {
  Serial.begin(57600);
  inputString.reserve(20);
  xString.reserve(10);
  yString.reserve(10);
  zString.reserve(10);
  arm.begin(basePin, shoulderPin, elbowPin, gripperPin);
  arm.gotoPointCylinder(x, y, z);
  Serial.println("Ready...");

}

void loop() {
	//Read joysticks
  if (analogRead(A0) > 600) {
    y = y - 2;
  }
  if (analogRead(A0) < 400) {
    y = y + 2;
  }

  y = constrain(y, 70, 210); //100,210
  Serial.print(y);

  if (analogRead(A1) > 600) {
    x = x - .02;
  }
  if (analogRead(A1) < 400) {
    x = x + .02;
  }
  x = constrain(x, -1.5, 1.5);
  Serial.print(" ");
  Serial.print(x);
  if (analogRead(A2) > 600) {
    z = z - 2;
  }
  if (analogRead(A2) < 400) {
    z = z + 2;
  }
  z = constrain(z, -30, 150); // -30, 120
  Serial.print(" ");
  Serial.println(z);

  if (analogRead(A3) > 600) {
  }
  if (analogRead(A3) < 400) {
    arm.closeGripper();
  } else {
    arm.openGripper();
    }
    
  parseCommand();
  arm.gotoPointCylinder(x, y, z);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void parseCommand() {
  if (stringComplete) {
    inputString.trim();
    int separatorIndex = inputString.indexOf(',');
    int separatorIndex2 = inputString.indexOf(',', separatorIndex + 1);
    int separatorIndex3 = inputString.indexOf(',', separatorIndex2 +1);
    xString = inputString.substring(0, separatorIndex);
    yString = inputString.substring(separatorIndex + 1, separatorIndex2);
    zString = inputString.substring(separatorIndex2 + 1);
    gString = inputString.substring(separatorIndex3 + 1);
    
    // There is no String.toFloat() function in Codebender ()Arduino 1.0.5) so here is a workaround!
    char buffer[10];
	xString.toCharArray(buffer, 10);
	x = atof(buffer);
	yString.toCharArray(buffer, 10);
	y = atof(buffer);
	zString.toCharArray(buffer, 10);
	z = atof(buffer);
    
    arm.gotoPointCylinder(x, y, z);
    if(gString=="1"){
    	arm.closeGripper();
    } else {
    	arm.closeGripper();
    }
    // clear the string:
    inputString = "";
    xString = "";
    yString = "";
    zString = "";
    stringComplete = false;
  }
}
