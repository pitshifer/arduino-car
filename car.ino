#include <Ultrasonic.h>
#include <SoftwareSerial.h>

#define RIGHT_1 2
#define RIGHT_2 3
#define RIGHT_EN 9
#define LEFT_1 4
#define LEFT_2 5
#define LEFT_EN 12

#define BT_RX 10
#define BT_TX 11

Ultrasonic ultrasonic(6, 7);
SoftwareSerial mySerial(BT_TX, BT_RX);

void setup() {
  pinMode(RIGHT_1, OUTPUT);
  pinMode(RIGHT_2, OUTPUT);
  pinMode(LEFT_1, OUTPUT);
  pinMode(LEFT_2, OUTPUT);
  pinMode(RIGHT_EN, OUTPUT);
  pinMode(LEFT_EN, OUTPUT);

  Serial.begin(9600);
  while(!Serial) {
    ;
  }

  Serial.println("Hello!");
  mySerial.begin(9600);
  mySerial.println("Are your hear me?");
}

void loop() {
  if (mySerial.available()) {
     char control = mySerial.read();
     switch(control) {
      case 'S':
        drive(0, 0);
        break;

      case 'F':
        drive(255, 255);
        break;

      case 'B':
        drive(-255, -255);
        break;

      case 'L':
        drive(-255, 255);
        break;

      case 'R':
        drive(255, -255);
        break;
     }
  }

  
//  long dist = ultrasonic.Ranging(1);
//
//  if (dist > 10) {
//    drive(170, 170);
//  } else if (dist < 10) {
//    drive(-170, -170);
//  } else {
//    avast();
//  }

  
//  drive(255, 255);
//  delay(2000);
//
//  drive(-255, -255);
//  delay(2000);
//
//  drive(255, 1);
//  delay(2000);
//
//  drive(1, 255);
//  delay(2000);
//
//  drive(255, -255);
//  delay(2000);
//
//  drive(-255, 255);
//  delay(2000);
}

void forward() {
  digitalWrite(RIGHT_1, HIGH);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(LEFT_1, HIGH);
  digitalWrite(LEFT_2, LOW);
}

void back() {
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, HIGH);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, HIGH);
}

void avast() {
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);
}

void drive(int left, int right) {
  if (left > 0) {
    digitalWrite(LEFT_1, HIGH);
    digitalWrite(LEFT_2, LOW);
  } else {
    digitalWrite(LEFT_1, LOW);
    digitalWrite(LEFT_2, HIGH);
  }
  analogWrite(LEFT_EN, abs(left));

  if (right > 0) {
    digitalWrite(RIGHT_1, HIGH);
    digitalWrite(RIGHT_2, LOW);
  } else {
    digitalWrite(RIGHT_1, LOW);
    digitalWrite(RIGHT_2, HIGH);
  }
  analogWrite(RIGHT_EN, abs(right));
}

void velocity(int degree) {
  analogWrite(RIGHT_EN, degree);
  analogWrite(LEFT_EN, degree);
}
