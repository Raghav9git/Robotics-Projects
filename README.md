#  Person-Following Robot (Arduino Project)

This is an Arduino-based robot that follows a person using an IR sensor and avoids obstacles using an ultrasonic sensor and a servo motor.

## Status: In Development

>  This code has **not yet been tested** with physical hardware. Expect bugs or behavior changes.

## Feedback Welcome

This is an early version of the project and is still untested on real hardware.  
**Feel free to suggest improvements, point out bugs, or share ideas!**

## Components Used
- Arduino Uno
- Adafruit Motor Shield
- 4 DC Motors
- IR Sensor
- Ultrasonic Sensor (HC-SR04)
- Servo Motor
- Power Supply (Battery Pack)

## Features
- Follows a person using IR sensor
- Avoids collisions using ultrasonic distance sensing
- Scans left and right using a servo when facing obstacles

## Libraries Required
- `AFMotor`
- `Servo`
- `NewPing`

Install these through the Arduino IDE's Library Manager.

## How It Works
- Starts moving forward when IR sensor detects someone
- Stops if an obstacle is within 30 cm
- Scans left and right to find an open path
- Turns toward the side with more space

---

## License
MIT License
