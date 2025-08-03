//A robot that follows a person where it goes
/* 1) for starting motion of robot
ir takes input
if high , motor forward
if low , no motor movement
 if ir high , us detects person at a specified distance and motor stops   // us=ultrasonic sensor

2)if person moves more forward
ir takes low as input
motors move forward
us detects person at a specified distance and motor stops
if again person moves more forward , same procedure

3) if person takes right and moves forward being at specified ditsance from robot
us takes input and moves motors to right + forward 

4) if person takes left and moves forward being at specified ditsance from robot
us takes input and moves motors to left + forward
*/


#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>

// --- Pin and robot config ---
#define TRIG_PIN A2
#define ECHO_PIN A3
#define MAX_DISTANCE 300
#define COLL_DIST 30
#define MAX_SPEED 160
#define MAX_SPEED_OFFSET 40

// --- Motors setup ---
AF_DCMotor leftMotor1(1, MOTOR12_1KHZ);
AF_DCMotor leftMotor2(2, MOTOR12_1KHZ);
AF_DCMotor rightMotor1(3, MOTOR34_1KHZ);
AF_DCMotor rightMotor2(4, MOTOR34_1KHZ);

// --- Servo and Ultrasonic ---
Servo myservo;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// --- Variables ---
int leftDistance, rightDistance;
int curDist = 0;
int irSensorPin = 2;
int irSensorState = 0;
String motorSet = "";
int speedSet = 0;

void setup() {
  myservo.attach(10);
  myservo.write(90);
  delay(3000);

  pinMode(irSensorPin, INPUT);
  Serial.begin(9600);

  irSensorState = digitalRead(irSensorPin);
  if (irSensorState == HIGH) {
    moveForward();
    delay(500);
  }
}

void loop() {
  myservo.write(90); // Look forward
  delay(500);

  curDist = readPing();
  Serial.print("Ultrasonic Distance: ");
  Serial.println(curDist);

  if (curDist < COLL_DIST) {
    moveStop();
  }

  irSensorState = digitalRead(irSensorPin);
  Serial.print("IR Sensor: ");
  Serial.println(irSensorState);

  if (irSensorState == LOW) {
    moveForward();
    delay(500);
  }
}

void moveStop() {
  stop();
  myservo.write(36);           // look right
  delay(500);
  rightDistance = readPing();

  myservo.write(144);          // look left
  delay(700);
  leftDistance = readPing();

  myservo.write(90); delay(500);
  compareDistance();
}

void compareDistance() {
  if (rightDistance < leftDistance) 
  {
    turnRight();                                  // turning right
  } 
  else if (leftDistance < rightDistance) 
  {
    turnLeft();                                   // turning left
  } 
  else 
  { 
    stop();
  }
}

int readPing() {
  delay(70);
  unsigned int uS = sonar.ping();
  int cm = uS / US_ROUNDTRIP_CM;
  if (cm == 0) cm = 999;            // shows path is clear and there is no object is within range
  return cm;
}

void stop() {
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

void turnRight() {
  motorSet = "RIGHT";
  leftMotor1.run(FORWARD);
  leftMotor2.run(FORWARD);
  rightMotor1.run(BACKWARD);
  rightMotor2.run(BACKWARD);

  leftMotor1.setSpeed(speedSet + MAX_SPEED_OFFSET);
  leftMotor2.setSpeed(speedSet + MAX_SPEED_OFFSET);
  rightMotor1.setSpeed(speedSet + MAX_SPEED_OFFSET);
  rightMotor2.setSpeed(speedSet + MAX_SPEED_OFFSET);

  delay(1500);
}

void turnLeft() {
  motorSet = "LEFT";
  leftMotor1.run(BACKWARD);
  leftMotor2.run(BACKWARD);
  rightMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);

  leftMotor1.setSpeed(speedSet + MAX_SPEED_OFFSET);
  leftMotor2.setSpeed(speedSet + MAX_SPEED_OFFSET);
  rightMotor1.setSpeed(speedSet + MAX_SPEED_OFFSET);
  rightMotor2.setSpeed(speedSet + MAX_SPEED_OFFSET);

  delay(1500);
}
