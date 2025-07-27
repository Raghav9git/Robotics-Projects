//# simple-Robot
//obstacle avoiding robot - Equipped with ultrasonic sensor and 4 motors + arduino uno +motor shield

#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>

// Define ultrasonic pins and robot settings
#define TRIG_PIN       A0
#define ECHO_PIN       A1
#define MAX_DISTANCE   300
#define COLL_DIST      30
#define MAX_SPEED      160
#define MAX_SPEED_OFFSET 40
#define TURN_DIST      COLL_DIST + 20

// Declare motors
AF_DCMotor leftMotor1(1, MOTOR12_1KHZ);
AF_DCMotor leftMotor2(2, MOTOR12_1KHZ);
AF_DCMotor rightMotor1(3, MOTOR34_1KHZ);
AF_DCMotor rightMotor2(4, MOTOR34_1KHZ);

// Declare servo and ultrasonic sensor
Servo myservo;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// Declare variables
int leftDistance, rightDistance;
int curDist = 0;
String motorSet = "";
int speedSet = 0;

void setup() {
  myservo.attach(10);       // attach servo to pin 10
  myservo.write(90);        // center the servo
  delay(3000);              // wait for 1 second
}





void loop() {
  myservo.write(90);         // Center the servo (look forward)
  delay(500);

  curDist = readPing();      // Read front distance

  if (curDist < COLL_DIST) {
    changePath();            // Too close? Try turning
  }

  moveForward();             // If clear, go forward
  delay(500);
}

void changePath() {
  moveStop();                // Stop motors
  myservo.write(36);         // Look right
  delay(500);
  rightDistance = readPing();
  delay(500);

  myservo.write(144);        // Look left
  delay(700);
  leftDistance = readPing();
  delay(500);

  myservo.write(90);         // Center servo again
  compareDistance();         // Decide which way to turn
}



void compareDistance() {
  if (leftDistance > rightDistance) {
    turnLeft();
  } else if (rightDistance > leftDistance) {
    turnRight();
  } else {
    turnAround();
  }
}

int readPing() {
  delay(70);
  unsigned int uS = sonar.ping();
  int cm = uS / US_ROUNDTRIP_CM;
  return cm;
}

void moveStop() {
  leftMotor1.run(RELEASE);
  leftMotor2.run(RELEASE);
  rightMotor1.run(RELEASE);
  rightMotor2.run(RELEASE);
}

void moveForward() {
  motorSet = "FORWARD";
  leftMotor1.run(FORWARD);
  leftMotor2.run(FORWARD);
  rightMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);
for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
  leftMotor1.setSpeed(speedSet);
  leftMotor2.setSpeed(speedSet);
  rightMotor1.setSpeed(speedSet);
  rightMotor2.setSpeed(speedSet);
  delay(5);
}
}

void moveBackward() {
  motorSet = "Backward";
  leftMotor1.run(BACKWARD);
  leftMotor2.run(BACKWARD);
  rightMotor1.run(BACKWARD);
  rightMotor2.run(BACKWARD);

  // Gradually increase speed
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
    leftMotor1.setSpeed(speedSet);
    leftMotor2.setSpeed(speedSet);
    rightMotor1.setSpeed(speedSet);
    rightMotor2.setSpeed(speedSet);
  }
}


void turnRight()
{
  motorSet="RIGHT";
  leftMotor1.run(FORWARD);
  leftMotor2.run(FORWARD);
  rightMotor1.run(BACKWARD);
  rightMotor2.run(BACKWARD);
  rightMotor1.setSpeed(speedSet+MAX_SPEED_OFFSET);
  rightMotor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
  delay(1500);
  motorSet="FORWARD";
  leftMotor1.run(FORWARD);
  leftMotor2.run(FORWARD);
  rightMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);
}


void turnLeft()
{
  motorSet="LEFT";
  leftMotor1.run(BACKWARD);
  leftMotor2.run(BACKWARD);
  rightMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);
  rightMotor1.setSpeed(speedSet+MAX_SPEED_OFFSET);
  rightMotor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
  delay(1500);
  motorSet="FORWARD";
  leftMotor1.run(FORWARD);
  leftMotor2.run(FORWARD);
  rightMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);
}


void turnAround()
{
  motorSet="LEFT";
  leftMotor1.run(BACKWARD);
  leftMotor2.run(BACKWARD);
  rightMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);
  rightMotor1.setSpeed(speedSet+MAX_SPEED_OFFSET);
  rightMotor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
  delay(3000);
  motorSet="FORWARD";
  leftMotor1.run(FORWARD);
  leftMotor2.run(FORWARD);
  rightMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);
}


